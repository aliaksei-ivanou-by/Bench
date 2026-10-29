// Добавляем данные измерения: скорость и timestamp с явными единицами.
// Комментарии описывают учебное поведение данного снимка, не весь готовый продукт.

// Учебный снимок: монитор ещё не завершён.
// Фиксированный целочисленный тип используется для времени в миллисекундах.
#include <cstdint>
// optional позволяет представить отсутствующий sample без фиктивной скорости.
#include <optional>
// Google Mock позволяет задавать поведение зависимостей и проверять их вызовы.
#include <gmock/gmock.h>
// Google Test предоставляет TEST, проверки EXPECT и запуск набора тестов.
#include <gtest/gtest.h>


namespace e506::wheel_speed {

// Время хранится в std::int64_t; суффикс _ms обозначает миллисекунды.
// Одно измерение: сама скорость и момент получения в той же системе часов.
struct SpeedSample { double speed_mps; std::int64_t timestamp_ms; };

// Проверяем тестовый runner; этот тест ничего не доказывает о мониторе.
TEST(Environment, TestFrameworkRuns) { EXPECT_EQ(1 + 1, 2); }

// Проверяем представление входных данных, а не алгоритм монитора.
TEST(DataContract, SampleStoresSpeedAndTimestamp) {
    const SpeedSample sample{20.0, 980};
    EXPECT_DOUBLE_EQ(sample.speed_mps, 20.0);
    EXPECT_EQ(sample.timestamp_ms, 980);
}

}  // namespace e506::wheel_speed

// Точка входа программы; Compiler Explorer выполняет именно её.
int main(int argc, char** argv) {
    // Инициализируем Google Mock и одновременно тестовый runner Google Test.
    ::testing::InitGoogleMock(&argc, argv);
    // Запускаем все зарегистрированные тесты; результат становится кодом выхода.
    return RUN_ALL_TESTS();
}
