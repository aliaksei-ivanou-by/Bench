gRPC

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Сети и протоколы
Релевантный scope: Типизированное межъязыковое взаимодействие сервисов вместо legacy JSON-RPC IPC.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

gRPC — RPC framework на основе service definitions и generated client/server APIs. Вместе с Protocol Buffers он поддерживает unary, client-streaming, server-streaming и bidirectional-streaming methods, обычно поверх HTTP/2.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Stub скрывает transport details, но вызов сохраняет семантику сетевых отказов.
- Deadlines, cancellation, metadata, interceptors и status codes образуют operational contract.
- Streaming добавляет flow control и управление lifetime сверх unary request.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Для каждого внешнего вызова нужен deadline; cancellation следует передавать дальше, retries разрешать только для idempotent operations и выбранных transient statuses, а interceptors использовать для auth и telemetry. Нужны mixed-version tests.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

gRPC даёт typed API, code generation и эффективный binary transport. Browser support и читаемость слабее REST/JSON, а schema governance обязательна. Async messaging лучше при необходимости temporal decoupling.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Retries без idempotency дублируют side effects.
- Отсутствие deadlines удерживает ресурсы при partial failure.
- Mapping всех внутренних ошибок в UNKNOWN ухудшает диагностику.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Кандидат спроектировал постепенную миграцию JSON-RPC→gRPC с параллельными adapters, переключением по method, shadow comparison, typed error mapping и OpenTelemetry-наблюдением. Заявленный результат — около 40% снижения serialization overhead и 60% уменьшения requests.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает gRPC?
Ответ: gRPC — RPC framework на основе service definitions и generated client/server APIs. Вместе с Protocol Buffers он поддерживает unary, client-streaming, server-streaming и bidirectional-streaming methods, обычно поверх HTTP/2.

2. Какие внутренние концепции важнее всего?
Ответ: Stub скрывает transport details, но вызов сохраняет семантику сетевых отказов. Deadlines, cancellation, metadata, interceptors и status codes образуют operational contract.

3. Что нужно явно определить в production design?
Ответ: Для каждого внешнего вызова нужен deadline; cancellation следует передавать дальше, retries разрешать только для idempotent operations и выбранных transient statuses, а interceptors использовать для auth и telemetry. Нужны mixed-version tests.

4. Каков основной компромисс или альтернатива?
Ответ: gRPC даёт typed API, code generation и эффективный binary transport. Browser support и читаемость слабее REST/JSON, а schema governance обязательна. Async messaging лучше при необходимости temporal decoupling.

5. Какой failure следует проверить первым?
Ответ: Retries без idempotency дублируют side effects. В контексте проекта: кандидат спроектировал постепенную миграцию JSON-RPC→gRPC с параллельными adapters, переключением по method, shadow comparison, typed error mapping и OpenTelemetry-наблюдением. Заявленный результат — около 40% снижения serialization overhead и 60% уменьшения requests.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://grpc.io/docs/what-is-grpc/core-concepts/
- https://grpc.io/docs/guides/
