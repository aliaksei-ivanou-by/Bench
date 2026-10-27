# Упражнение 3: Ограничитель команды рулевого управления

## Цель

Реализовать компонент, который валидирует и ограничивает requested steering-assistance torque перед отправкой в actuator.

Таймбокс: 60 минут.

Предлагаемые файлы:

- `SteeringCommandLimiter.h`
- `SteeringCommandLimiter.cpp`
- `SteeringCommandLimiterTest.cpp`

## Комплект кода

- `include/SteeringCommandLimiter.h` задаёт команду, порты и наблюдаемое состояние.
- `tests/SteeringCommandLimiterTest.cpp` покрывает абсолютное ограничение, скорость изменения, время и отказы.
- `solution/SteeringCommandLimiter.cpp` содержит эталонное решение.
- `CMakeLists.txt` по умолчанию собирает эталонное решение.

Для тренировки нужно создать `work/SteeringCommandLimiter.cpp` и сконфигурировать эту папку командами:

```text
cmake -S . -B build -DSTEERING_LIMITER_IMPLEMENTATION="$PWD/work/SteeringCommandLimiter.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

Тестовый набор проверяет как вызовы actuator, так и состояние, сохранённое после отклонения команды.

## Шаг 1: Задать вопросы до кодирования

- Каковы единицы torque и абсолютный предел?
- Какова допустимая скорость изменения torque?
- Rate рассчитывается по фиксированным циклам или elapsed time?
- Когда input считается stale?
- Что происходит при driver override?
- Какова safe command при недопустимом времени или данных?
- Обновляется ли последнее состояние при отказе actuator?
- Команды отправляются каждый цикл или только при изменении?

## Шаг 2: Согласованные требования

- REQ-SCL-001: Requested torque должна быть finite.
- REQ-SCL-002: Input старше 50 ms считается stale.
- REQ-SCL-003: Absolute torque ограничивается диапазоном ±3,0 Nm.
- REQ-SCL-004: Скорость изменения ограничивается 50,0 Nm/s по monotonic elapsed time.
- REQ-SCL-005: Driver override запрашивает 0,0 Nm assistance.
- REQ-SCL-006: Нулевое или отрицательное elapsed time не вызывает actuator и сообщает `InvalidTime`.
- REQ-SCL-007: Stale или invalid input не вызывает actuator и сообщает fault.
- REQ-SCL-008: Последняя принятая команда меняется только после успешного actuator call.

## Шаг 3: Определить mocks

- Command input port.
- Monotonic clock.
- Steering actuator.
- Diagnostic sink.

## Шаг 4: Написать тесты

1. Обычная команда внутри обоих ограничений.
2. Точные границы +3,0 и -3,0 Nm.
3. Команды выше и ниже абсолютных пределов ограничиваются.
4. Положительный rate limit.
5. Отрицательный rate limit.
6. Переменное elapsed time меняет допустимую delta.
7. Нулевое и отрицательное elapsed time отклоняются.
8. NaN и infinity отклоняются.
9. Команда возрастом 50 ms принимается, 51 ms считается stale.
10. Driver override задаёт нулевую assistance.
11. Отказ actuator сохраняет предыдущее принятое состояние.

## Шаг 5: Реализовать

- Сначала проверить input и время.
- Вывести допустимую delta из elapsed time.
- Применить rate limit, затем absolute limit в согласованном порядке.
- Хранить последний принятый output как явное состояние.
- Обновлять состояние только после успеха actuator.

## Шаг 6: Объяснить границы верификации

- Unit tests доказывают arithmetic, ordering и state transitions.
- Integration tests должны проверить units и actuator protocol.
- Target tests должны проверить timing jitter и execution deadlines.
- HIL или vehicle tests должны проверить driver override и фактическую реакцию рулевого управления.

## Вопрос по ASIL

Непреднамеренное рулевое воздействие на скорости может иметь высокую severity, но кандидат должен запросить item, operating situation и safe reaction. Zero torque, controlled ramp-down и handover другому controller являются разными требованиями, их нельзя угадывать.

## Критерии готовности

- Проходят одиннадцать сценариев.
- В классе нет скрытого обращения к system time.
- NaN и invalid time обработаны.
- Порядок ограничений задан и протестирован.
- Неуспешный actuator call не повреждает внутреннее состояние.

## Дополнительные усложнения

- Добавить command sequence numbers.
- Добавить отдельные enable и availability states.
- Добавить политику controlled ramp-down.
- Добавить strong torque и time types.

