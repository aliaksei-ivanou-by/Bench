// GREEN: добавляем отдельный счётчик восстановления и его сброс.
// Комментарии описывают учебное поведение данного снимка, не весь готовый продукт.

// Teaching snapshot: incomplete stages are intentionally not production code.


// Фиксированный целочисленный тип используется для времени в миллисекундах.
#include <cstdint>
// optional позволяет представить отсутствующий sample без фиктивной скорости.
#include <optional>

namespace e506::wheel_speed {

// Явно называем единицу времени, чтобы не спутать миллисекунды и секунды.
using Milliseconds = std::int64_t;

// Одно измерение: сама скорость и момент получения в той же системе часов.
struct SpeedSample {
    // Скорость выражена в метрах в секунду; диапазон проверяется в tick.
    double speed_mps;
    // Timestamp нужен для проверки возраста и должен использовать источник времени clock.
    Milliseconds timestamp_ms;
};

// Публичное состояние: данные доступны либо работа деградировала.
enum class Status {
    Available,
    Degraded
};

// Диагностика уточняет причину, отдельно от публикуемого статуса.
enum class Diagnostic {
    MissingSample,
    StaleSample,
    InvalidSample
};

// Граница источника скорости; реальное устройство можно заменить mock-объектом.
class ISpeedSensor {
public:
    // Виртуальный деструктор нужен для корректного удаления через интерфейс.
    virtual ~ISpeedSensor() = default;
    // Пустой optional означает отсутствие измерения, а не нулевую скорость.
    virtual std::optional<SpeedSample> read() = 0;
};

// Часы внедряются извне, чтобы контролировать время в тестах.
class IMonotonicClock {
public:
    // Виртуальный деструктор нужен для корректного удаления через интерфейс.
    virtual ~IMonotonicClock() = default;
    // Время читается через зависимость; метод const не меняет её интерфейсное состояние.
    virtual Milliseconds nowMs() const = 0;
};

// Через этот порт компонент сообщает об изменении доступности.
class IStatusOutput {
public:
    // Виртуальный деструктор нужен для корректного удаления через интерфейс.
    virtual ~IStatusOutput() = default;
    // Публикация является наблюдаемым внешним эффектом, который проверит mock.
    virtual void publish(Status status) = 0;
};

// Отдельный порт сообщает причину ошибки и не является самим статусом.
class IDiagnosticSink {
public:
    // Виртуальный деструктор нужен для корректного удаления через интерфейс.
    virtual ~IDiagnosticSink() = default;
    // Сообщение диагностики передаётся отдельно от перехода статуса.
    virtual void report(Diagnostic diagnostic) = 0;
};

// Компонент хранит состояние и ссылки на внешние порты; он не владеет устройствами.
class WheelSpeedMonitor {
public:
    // Конструктор получает зависимости: тест может передать mocks вместо устройств.
    WheelSpeedMonitor(ISpeedSensor& primary,
                      ISpeedSensor& secondary,
                      const IMonotonicClock& clock,
                      IStatusOutput& output,
                      IDiagnosticSink& diagnostics);

    // Один вызов соответствует одному циклу; расписание вызовов находится снаружи.
    void tick();
    // Возвращаем наблюдаемый статус без побочных эффектов.
    Status status() const noexcept;

private:
    // Общая точка смены состояния нужна для подавления повторных публикаций.
    void enter(Status next);
    // Общий путь немедленного отказа сообщает причину и переводит статус.
    void degradeImmediately(Diagnostic diagnostic);

    // Основной сенсор передаётся по ссылке и должен жить дольше монитора.
    ISpeedSensor& primary_;
    // Резервный сенсор — отдельный экземпляр того же интерфейса.
    ISpeedSensor& secondary_;
    // Храним ссылку на часы; время остаётся контролируемым извне.
    const IMonotonicClock& clock_;
    // Через output_ отправляем только наблюдаемые изменения статуса.
    IStatusOutput& output_;
    // Сюда отправляются причины ошибок; сам монитор не владеет sink.
    IDiagnosticSink& diagnostics_;
    // Начальное Available задано учебным контрактом; это не универсальная политика для автомобиля.
    Status status_{Status::Available};
    // Считаем последовательные неправдоподобные пары до деградации.
    unsigned bad_cycles_{0};
    // Отдельно считаем последовательные хорошие пары после деградации.
    unsigned recovery_cycles_{0};
};

}  // namespace e506::wheel_speed

// Нужны fabs для разницы и, на следующих этапах, isfinite для валидации.
#include <cmath>

namespace e506::wheel_speed {
WheelSpeedMonitor::WheelSpeedMonitor(ISpeedSensor& primary, ISpeedSensor& secondary,
    const IMonotonicClock& clock, IStatusOutput& output, IDiagnosticSink& diagnostics)
    : primary_(primary), secondary_(secondary), clock_(clock),
      output_(output), diagnostics_(diagnostics) {}

Status WheelSpeedMonitor::status() const noexcept { return status_; }

// Переход централизован: одинаковое состояние повторно не публикуется.
void WheelSpeedMonitor::enter(Status next) {
    // Если состояние не изменилось, внешний вызов publish не нужен.
    if (next == status_) return;
    status_ = next;
    output_.publish(status_);
}

// Отдельный путь для отсутствующих, устаревших и некорректных данных.
void WheelSpeedMonitor::degradeImmediately(Diagnostic diagnostic) {
    // Прерываем последовательность плохих циклов: старая история больше не действует.
    bad_cycles_ = 0;
    // Прерываем восстановление: хорошие циклы потребуется накопить заново.
    recovery_cycles_ = 0;
    // Сообщаем причину сбоя независимо от того, изменится ли статус.
    diagnostics_.report(diagnostic);
    enter(Status::Degraded);
}

void WheelSpeedMonitor::tick() {
    // За этот цикл читаем основной сенсор ровно один раз.
    const auto primary = primary_.read();
    // Отдельно читаем резервный сенсор; порядок сравнения не делает его истинным.
    const auto secondary = secondary_.read();
    // Проверяем наличие обоих измерений до обращения к полям optional.
    if (!primary || !secondary) {
        // Отсутствие хотя бы одного sample немедленно ухудшает статус и создаёт диагностику.
        degradeImmediately(Diagnostic::MissingSample);
        return;
    }
    // Одно значение часов используется для согласованной проверки обоих timestamps.
    const auto now = clock_.nowMs();
    // Будущий timestamp недопустим: нельзя считать его отрицательным возрастом.
    if (primary->timestamp_ms > now || secondary->timestamp_ms > now) {
        degradeImmediately(Diagnostic::InvalidSample);
        return;
    }
    // Возраст больше 50 ms недопустим; ровно 50 ms допускается учебным контрактом.
    if (now - primary->timestamp_ms > 50 || now - secondary->timestamp_ms > 50) {
        degradeImmediately(Diagnostic::StaleSample);
        return;
    }
    // Сначала проверяем конечность и диапазон, затем можно сравнивать скорости.
    const auto valid = [](double v) {
        return std::isfinite(v) && v >= 0.0 && v <= 100.0;
    };
    if (!valid(primary->speed_mps) || !valid(secondary->speed_mps)) {
        degradeImmediately(Diagnostic::InvalidSample);
        return;
    }
    // Оба входа уже проверены; сравниваем абсолютное расхождение с порогом.
    const bool plausible = std::fabs(primary->speed_mps - secondary->speed_mps) <= 1.5;
    // В Available анализируем последовательность плохих, а не цикл восстановления.
    if (status_ == Status::Available) {
        // Хорошая пара прерывает серию предыдущих расхождений.
        if (plausible) { bad_cycles_ = 0; return; }
        // Увеличиваем счётчик только для плохой пригодной пары.
        ++bad_cycles_;
        // На третьем подряд расхождении меняем статус и очищаем серию.
        if (bad_cycles_ >= 3) { bad_cycles_ = 0; enter(Status::Degraded); }
        return;
    }
    // Плохая пара во время восстановления прерывает серию хороших циклов.
    if (!plausible) { recovery_cycles_ = 0; return; }
    // Считаем только последовательные хорошие циклы в состоянии Degraded.
    ++recovery_cycles_;
    // Пятая хорошая пара завершает восстановление и публикует Available.
    if (recovery_cycles_ >= 5) { recovery_cycles_ = 0; enter(Status::Available); }
}
}


// Google Mock позволяет задавать поведение зависимостей и проверять их вызовы.
#include <gmock/gmock.h>
// Google Test предоставляет TEST, проверки EXPECT и запуск набора тестов.
#include <gtest/gtest.h>

// Через numeric_limits тесты получают NaN и бесконечность.
#include <limits>
// optional позволяет представить отсутствующий sample без фиктивной скорости.
#include <optional>

namespace e506::wheel_speed {
namespace {

using ::testing::Return;
using ::testing::StrictMock;

// Тестовая замена соответствующего порта: реальные I/O здесь не выполняются.
class MockSensor : public ISpeedSensor {
public:
    // gMock создаёт переопределение, поведение и ожидаемые вызовы задаются в тесте.
    MOCK_METHOD(std::optional<SpeedSample>, read, (), (override));
};

// Тестовая замена соответствующего порта: реальные I/O здесь не выполняются.
class MockClock : public IMonotonicClock {
public:
    // gMock создаёт переопределение, поведение и ожидаемые вызовы задаются в тесте.
    MOCK_METHOD(Milliseconds, nowMs, (), (const, override));
};

// Тестовая замена соответствующего порта: реальные I/O здесь не выполняются.
class MockStatusOutput : public IStatusOutput {
public:
    // gMock создаёт переопределение, поведение и ожидаемые вызовы задаются в тесте.
    MOCK_METHOD(void, publish, (Status), (override));
};

// Тестовая замена соответствующего порта: реальные I/O здесь не выполняются.
class MockDiagnosticSink : public IDiagnosticSink {
public:
    // gMock создаёт переопределение, поведение и ожидаемые вызовы задаются в тесте.
    MOCK_METHOD(void, report, (Diagnostic), (override));
};

// Fixture создаёт новый набор mocks и монитор для каждого теста.
class WheelSpeedMonitorTest : public ::testing::Test {
protected:
    // Вспомогательная настройка ожидает чтение обоих сенсоров и, при наличии данных, часов.
    void expectCycle(std::optional<SpeedSample> primary,
                     std::optional<SpeedSample> secondary,
                     Milliseconds now = 1000) {
        // Ожидаем один read и возвращаем значение, заданное конкретным циклом теста.
        EXPECT_CALL(primary_, read()).WillOnce(Return(primary));
        // Аналогично задаём независимое значение второго сенсора.
        EXPECT_CALL(secondary_, read()).WillOnce(Return(secondary));
        if (primary && secondary) {
            // Часы возвращают известный now; в тесте не зависит от реального времени.
            EXPECT_CALL(clock_, nowMs()).WillOnce(Return(now));
        }
    }

    // Создаём компактный sample; по умолчанию его возраст при now = 1000 равен 20 ms.
    SpeedSample sample(double value, Milliseconds timestamp = 980) const {
        return {value, timestamp};
    }

    // StrictMock превращает неожиданные вызовы основного сенсора в ошибку теста.
    StrictMock<MockSensor> primary_;
    // Второй экземпляр mock представляет независимый резервный вход.
    StrictMock<MockSensor> secondary_;
    StrictMock<MockClock> clock_;
    StrictMock<MockStatusOutput> output_;
    StrictMock<MockDiagnosticSink> diagnostics_;
    // Собираем проверяемый компонент из уже созданных mocks; их время жизни достаточно.
    WheelSpeedMonitor monitor_{primary_, secondary_, clock_, output_, diagnostics_};
};


// Проверяем только начальное состояние; tick в этом тесте не вызывается.
TEST_F(WheelSpeedMonitorTest, InitialStateIsAvailable) {
    // Проверяем наблюдаемое состояние после обработки цикла.
    EXPECT_EQ(monitor_.status(), Status::Available);
}

// При равных скоростях состояние остаётся Available и публикации нет.
TEST_F(WheelSpeedMonitorTest, EqualValuesKeepAvailableWithoutNotification) {
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(sample(20.0), sample(20.0));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
    // Проверяем наблюдаемое состояние после обработки цикла.
    EXPECT_EQ(monitor_.status(), Status::Available);
}

// Два расхождения недостаточны; третье должно опубликовать Degraded.
TEST_F(WheelSpeedMonitorTest, ThirdConsecutiveBadCycleDegrades) {
    for (int cycle = 0; cycle < 2; ++cycle) {
        // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
        expectCycle(sample(20.0), sample(21.6));
        // Выполняем один цикл монитора на заранее настроенных mock-входах.
        monitor_.tick();
    }
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(sample(20.0), sample(21.6));
    // Ожидаем конкретную публикацию; StrictMock обнаружит неожиданные дополнительные вызовы.
    EXPECT_CALL(output_, publish(Status::Degraded));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
    // Проверяем наблюдаемое состояние после обработки цикла.
    EXPECT_EQ(monitor_.status(), Status::Degraded);
}

// Хороший цикл прерывает последовательность ошибок: старые и новые не складываются.
TEST_F(WheelSpeedMonitorTest, PlausibleCycleResetsBadCounter) {
    for (int cycle = 0; cycle < 2; ++cycle) {
        // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
        expectCycle(sample(20.0), sample(21.6));
        // Выполняем один цикл монитора на заранее настроенных mock-входах.
        monitor_.tick();
    }
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(sample(20.0), sample(20.5));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
    for (int cycle = 0; cycle < 2; ++cycle) {
        // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
        expectCycle(sample(20.0), sample(21.6));
        // Выполняем один цикл монитора на заранее настроенных mock-входах.
        monitor_.tick();
    }
    // Проверяем наблюдаемое состояние после обработки цикла.
    EXPECT_EQ(monitor_.status(), Status::Available);
}

// Отсутствие входа отличается от расхождения: реакция должна быть немедленной.
TEST_F(WheelSpeedMonitorTest, MissingSensorDegradesImmediately) {
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(std::nullopt, sample(20.0));
    // Ожидаем конкретную причину ошибки, а не только изменение статуса.
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    // Ожидаем конкретную публикацию; StrictMock обнаружит неожиданные дополнительные вызовы.
    EXPECT_CALL(output_, publish(Status::Degraded));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
}

// Проверяем, что возраст 51 ms уже вызывает StaleSample.
TEST_F(WheelSpeedMonitorTest, FiftyOneMillisecondSampleIsStale) {
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(sample(20.0, 949), sample(20.5, 950));
    // Ожидаем конкретную причину ошибки, а не только изменение статуса.
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleSample));
    // Ожидаем конкретную публикацию; StrictMock обнаружит неожиданные дополнительные вызовы.
    EXPECT_CALL(output_, publish(Status::Degraded));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
}

// NaN не должен пройти сравнение как нормальное измерение.
TEST_F(WheelSpeedMonitorTest, NaNDegradesImmediately) {
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(sample(std::numeric_limits<double>::quiet_NaN()), sample(20.0));
    // Ожидаем конкретную причину ошибки, а не только изменение статуса.
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidSample));
    // Ожидаем конкретную публикацию; StrictMock обнаружит неожиданные дополнительные вызовы.
    EXPECT_CALL(output_, publish(Status::Degraded));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
}

// После деградации четыре хороших цикла недостаточны, пятый восстанавливает статус.
TEST_F(WheelSpeedMonitorTest, FifthPlausibleCycleRecovers) {
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(std::nullopt, sample(20.0));
    // Ожидаем конкретную причину ошибки, а не только изменение статуса.
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    // Ожидаем конкретную публикацию; StrictMock обнаружит неожиданные дополнительные вызовы.
    EXPECT_CALL(output_, publish(Status::Degraded));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();

    for (int cycle = 0; cycle < 4; ++cycle) {
        // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
        expectCycle(sample(20.0), sample(20.5));
        // Выполняем один цикл монитора на заранее настроенных mock-входах.
        monitor_.tick();
        // Проверяем наблюдаемое состояние после обработки цикла.
        EXPECT_EQ(monitor_.status(), Status::Degraded);
    }
    // Задаём входы для следующего tick и ожидания взаимодействия с зависимостями.
    expectCycle(sample(20.0), sample(20.5));
    // Ожидаем конкретную публикацию; StrictMock обнаружит неожиданные дополнительные вызовы.
    EXPECT_CALL(output_, publish(Status::Available));
    // Выполняем один цикл монитора на заранее настроенных mock-входах.
    monitor_.tick();
    // Проверяем наблюдаемое состояние после обработки цикла.
    EXPECT_EQ(monitor_.status(), Status::Available);
}

}  // namespace
}  // namespace e506::wheel_speed

// Точка входа программы; Compiler Explorer выполняет именно её.
int main(int argc, char** argv) {
    // Инициализируем Google Mock и одновременно тестовый runner Google Test.
    ::testing::InitGoogleMock(&argc, argv);
    // Запускаем все зарегистрированные тесты; результат становится кодом выхода.
    return RUN_ALL_TESTS();
}
