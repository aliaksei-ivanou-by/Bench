// Добавляем перечисления состояния монитора и возможных диагностик.
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

}  // namespace e506::wheel_speed

// Точка входа программы; Compiler Explorer выполняет именно её.
int main(int argc, char** argv) {
    // Инициализируем Google Mock и одновременно тестовый runner Google Test.
    ::testing::InitGoogleMock(&argc, argv);
    // Запускаем все зарегистрированные тесты; результат становится кодом выхода.
    return RUN_ALL_TESTS();
}
