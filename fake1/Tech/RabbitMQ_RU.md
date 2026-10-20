RabbitMQ

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Базы данных и messaging
Релевантный scope: Message broker в широком окружении платформы.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

RabbitMQ — message broker, обычно реализующий AMQP 0-9-1. Producers публикуют в exchanges; bindings направляют messages в queues; consumers подтверждают deliveries после обработки.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Exchange type определяет routing по key, pattern, broadcast или headers.
- Publisher confirms и consumer acknowledgements покрывают разные половины delivery.
- Durability, persistence и quorum queues повышают resilience ценой latency/resources.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Consumers должны быть idempotent; prefetch — bounded; retry и dead-letter policy — явными. Следует наблюдать age очереди, а poison messages отделять от transient failures.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

RabbitMQ даёт гибкий routing и operational tooling, но не обеспечивает exactly-once processing. Kafka подходит для durable ordered log, cloud queues уменьшают operations, direct RPC проще для immediate response.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Ack до durable side effect теряет работу.
- Неограниченный redelivery loop создаёт инцидент.
- Large messages и unbounded queues исчерпывают memory/disk.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

RabbitMQ входил в окружение проекта; конкретный RabbitMQ design или личная ответственность не входили в заявленный scope.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает RabbitMQ?
Ответ: RabbitMQ — message broker, обычно реализующий AMQP 0-9-1. Producers публикуют в exchanges; bindings направляют messages в queues; consumers подтверждают deliveries после обработки.

2. Какие внутренние концепции важнее всего?
Ответ: Exchange type определяет routing по key, pattern, broadcast или headers. Publisher confirms и consumer acknowledgements покрывают разные половины delivery.

3. Что нужно явно определить в production design?
Ответ: Consumers должны быть idempotent; prefetch — bounded; retry и dead-letter policy — явными. Следует наблюдать age очереди, а poison messages отделять от transient failures.

4. Каков основной компромисс или альтернатива?
Ответ: RabbitMQ даёт гибкий routing и operational tooling, но не обеспечивает exactly-once processing. Kafka подходит для durable ordered log, cloud queues уменьшают operations, direct RPC проще для immediate response.

5. Какой failure следует проверить первым?
Ответ: Ack до durable side effect теряет работу. В контексте проекта: rabbitMQ входил в окружение проекта; конкретный RabbitMQ design или личная ответственность не входили в заявленный scope.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://www.rabbitmq.com/docs
- https://www.rabbitmq.com/docs/confirms
