// Проверяем, что Google Test и Google Mock подключены и тестовый runner запускается.
// Комментарии описывают учебное поведение данного снимка, не весь готовый продукт.

// Google Mock позволяет задавать поведение зависимостей и проверять их вызовы.
#include <gmock/gmock.h>
// Google Test предоставляет TEST, проверки EXPECT и запуск набора тестов.
#include <gtest/gtest.h>

// Проверяем тестовый runner; этот тест ничего не доказывает о мониторе.
TEST(Environment, TestFrameworkRuns) { EXPECT_EQ(1 + 1, 2); }

// Точка входа программы; Compiler Explorer выполняет именно её.
int main(int argc, char** argv) {
    // Инициализируем Google Mock и одновременно тестовый runner Google Test.
    ::testing::InitGoogleMock(&argc, argv);
    // Запускаем все зарегистрированные тесты; результат становится кодом выхода.
    return RUN_ALL_TESTS();
}
