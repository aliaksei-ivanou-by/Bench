JSON-RPC

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Сети и протоколы
Релевантный scope: Legacy-протокол межпроцессного взаимодействия, заменённый на gRPC и Protobuf.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

JSON-RPC 2.0 — transport-agnostic request/response protocol на JSON-объектах. Request содержит jsonrpc, method, optional params и id; notification не имеет id; response содержит result либо error.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Спецификация определяет форму сообщений, но не transport, discovery, schema или authentication.
- Batch requests группируют независимые calls, но не дают transactionality.
- Errors содержат numeric code, message и optional data.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Нужно валидировать version и shape, документировать method contracts, ограничивать payload и отдельно определять timeout, idempotency и transport behavior. Mixed result/error response должен отклоняться.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

JSON-RPC прост, читаем и удобен для debug, но не имеет встроенной typed schema и generated compatibility contract. REST ориентирован на resources, gRPC типизирован и эффективен, messaging развязывает producers/consumers.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- String method names и dynamic params переносят ошибки в runtime.
- Notifications не дают application-level response.
- Большие JSON payloads увеличивают allocation и serialization cost.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Платформа использовала JSON-RPC IPC до введения параллельного gRPC/Protobuf пути; методы отключались постепенно после проверки эквивалентности и производительности.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает JSON-RPC?
Ответ: JSON-RPC 2.0 — transport-agnostic request/response protocol на JSON-объектах. Request содержит jsonrpc, method, optional params и id; notification не имеет id; response содержит result либо error.

2. Какие внутренние концепции важнее всего?
Ответ: Спецификация определяет форму сообщений, но не transport, discovery, schema или authentication. Batch requests группируют независимые calls, но не дают transactionality.

3. Что нужно явно определить в production design?
Ответ: Нужно валидировать version и shape, документировать method contracts, ограничивать payload и отдельно определять timeout, idempotency и transport behavior. Mixed result/error response должен отклоняться.

4. Каков основной компромисс или альтернатива?
Ответ: JSON-RPC прост, читаем и удобен для debug, но не имеет встроенной typed schema и generated compatibility contract. REST ориентирован на resources, gRPC типизирован и эффективен, messaging развязывает producers/consumers.

5. Какой failure следует проверить первым?
Ответ: String method names и dynamic params переносят ошибки в runtime. В контексте проекта: платформа использовала JSON-RPC IPC до введения параллельного gRPC/Protobuf пути; методы отключались постепенно после проверки эквивалентности и производительности.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://www.jsonrpc.org/specification
