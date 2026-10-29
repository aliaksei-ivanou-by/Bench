// Добавляем интерфейс monotonic clock и mock с предсказуемым временем.
// Комментарии описывают учебное поведение данного снимка, не весь готовый продукт.

// Teaching snapshot: this is not a complete monitor.
// Фиксированный целочисленный тип используется для времени в миллисекундах.
#include <cstdint>
// optional позволяет представить отсутствующий sample без фиктивной скорости.
#include <optional>
// Google Mock позволяет задавать поведение зависимостей и проверять их вызовы.
#include <gmock/gmock.h>
// Google Test предоставляет TEST, проверки EXPECT и запуск набора тестов.
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::StrictMock;

namespace e506::wheel_speed {

// Явно называем единицу времени, чтобы не спутать миллисекунды и секунды.
using Milliseconds = std::int64_t;
// Одно измерение: сама скорость и момент получения в той же системе часов.
struct SpeedSample { double speed_mps; Milliseconds timestamp_ms; };

// Публичное состояние: данные доступны либо работа деградировала.
enum class Status { Available, Degraded };
// Диагностика уточняет причину, отдельно от публикуемого статуса.
enum class Diagnostic { MissingSample, StaleSample, InvalidSample };

// Граница источника скорости; реальное устройство можно заменить mock-объектом.
class ISpeedSensor {
public:
    // Виртуальный деструктор нужен для корректного удаления через интерфейс.
    virtual ~ISpeedSensor() = default;
    // Пустой optional означает отсутствие измерения, а не нулевую скорость.
    virtual std::optional<SpeedSample> read() = 0;
};
// Тестовая замена соответствующего порта: реальные I/O здесь не выполняются.
class MockSensor : public ISpeedSensor {
public:
    // gMock создаёт переопределение, поведение и ожидаемые вызовы задаются в тесте.
    MOCK_METHOD(std::optional<SpeedSample>, read, (), (override));
};

// Часы внедряются извне, чтобы контролировать время в тестах.
class IMonotonicClock {
public:
    // Виртуальный деструктор нужен для корректного удаления через интерфейс.
    virtual ~IMonotonicClock() = default;
    // Время читается через зависимость; метод const не меняет её интерфейсное состояние.
    virtual Milliseconds nowMs() const = 0;
};
// Тестовая замена соответствующего порта: реальные I/O здесь не выполняются.
class MockClock : public IMonotonicClock {
public:
    // gMock создаёт переопределение, поведение и ожидаемые вызовы задаются в тесте.
    MOCK_METHOD(Milliseconds, nowMs, (), (const, override));
};

// Проверяем тестовый runner; этот тест ничего не доказывает о мониторе.
TEST(Environment, TestFrameworkRuns) { EXPECT_EQ(1 + 1, 2); }

// Проверяем представление входных данных, а не алгоритм монитора.
TEST(DataContract, SampleStoresSpeedAndTimestamp) {
    const SpeedSample sample{20.0, 980};
    EXPECT_DOUBLE_EQ(sample.speed_mps, 20.0);
    EXPECT_EQ(sample.timestamp_ms, 980);
}

// Убеждаемся, что два наблюдаемых состояния различимы.
TEST(DataContract, StatusValuesAreDistinct) {
    EXPECT_NE(Status::Available, Status::Degraded);
}

// Пример настройки mock: здесь сенсор вызывается тестом напрямую.
TEST(Ports, SensorReturnsConfiguredSample) {
    StrictMock<MockSensor> sensor;
    EXPECT_CALL(sensor, read()).WillOnce(Return(SpeedSample{20.0, 980}));
    const auto result = sensor.read();
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->speed_mps, 20.0);
}

// Фиксированное время делает тест детерминированным; настоящие часы не нужны.
TEST(Ports, ClockReturnsConfiguredTime) {
    StrictMock<MockClock> clock;
    EXPECT_CALL(clock, nowMs()).WillOnce(Return(1000));
    EXPECT_EQ(clock.nowMs(), 1000);
}

}  // namespace e506::wheel_speed

// Точка входа программы; Compiler Explorer выполняет именно её.
int main(int argc, char** argv) {
    // Инициализируем Google Mock и одновременно тестовый runner Google Test.
    ::testing::InitGoogleMock(&argc, argv);
    // Запускаем все зарегистрированные тесты; результат становится кодом выхода.
    return RUN_ALL_TESTS();
}
