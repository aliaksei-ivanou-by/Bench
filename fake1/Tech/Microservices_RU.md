Микросервисная архитектура

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Архитектура
Релевантный scope: Распределённая сервисная архитектура cloud-native платформы кодирования и доставки.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

Микросервисы делят систему на независимо развёртываемые services вокруг ограниченных responsibilities. Каждый service владеет поведением и предоставляет contracts, а продукт становится distributed system с сетевыми и operational failures.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Boundaries должны следовать change/ownership, а не только technical layers.
- Synchronous RPC создаёт temporal coupling; messages меняют immediate response на decoupling.
- Independent deployment требует contract compatibility, observability и automation.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Нужно определять ownership и SLO, versionable contracts, изолировать failure через deadlines/bounded queues, передавать trace context и избегать shared-database coupling.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

Микросервисы поддерживают autonomy и selective scaling, но усложняют deployment, testing и incidents. Modular monolith часто лучше, пока независимое масштабирование или ownership не оправдывает distribution.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Chatty synchronous chains умножают tail latency.
- Retries без budgets создают retry storm.
- Преждевременное разделение даёт distributed monolith.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Проект описан как distributed microservice platform в трёх availability zones с C++20, Java и Kotlin. Кандидат отвечал за выбранные communication, output, telemetry и media concerns, а не за всю платформу.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает Микросервисная архитектура?
Ответ: Микросервисы делят систему на независимо развёртываемые services вокруг ограниченных responsibilities. Каждый service владеет поведением и предоставляет contracts, а продукт становится distributed system с сетевыми и operational failures.

2. Какие внутренние концепции важнее всего?
Ответ: Boundaries должны следовать change/ownership, а не только technical layers. Synchronous RPC создаёт temporal coupling; messages меняют immediate response на decoupling.

3. Что нужно явно определить в production design?
Ответ: Нужно определять ownership и SLO, versionable contracts, изолировать failure через deadlines/bounded queues, передавать trace context и избегать shared-database coupling.

4. Каков основной компромисс или альтернатива?
Ответ: Микросервисы поддерживают autonomy и selective scaling, но усложняют deployment, testing и incidents. Modular monolith часто лучше, пока независимое масштабирование или ownership не оправдывает distribution.

5. Какой failure следует проверить первым?
Ответ: Chatty synchronous chains умножают tail latency. В контексте проекта: проект описан как distributed microservice platform в трёх availability zones с C++20, Java и Kotlin. Кандидат отвечал за выбранные communication, output, telemetry и media concerns, а не за всю платформу.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://learn.microsoft.com/en-us/azure/architecture/guide/architecture-styles/microservices
- https://microservices.io/
