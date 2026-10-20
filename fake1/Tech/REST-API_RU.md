REST API

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Сети и протоколы
Релевантный scope: HTTP resource API в широком окружении платформы и для настройки политики output.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

REST — architectural style вокруг resources, representations, uniform interface и stateless interactions. В практическом HTTP API поведение задают methods, status codes, headers, media types, caching и links.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Resource identifiers должны быть стабильными и не зависеть от операции.
- Safety и idempotency HTTP methods определяют retries и caching.
- Representations — versioned contracts; status codes описывают protocol outcomes.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Следует моделировать nouns, а не RPC verbs, валидировать inputs, согласовать pagination и errors, применять conditional requests и публиковать OpenAPI contract, если он принят командой.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

REST/JSON доступен и browser-friendly, но verbose и слабее типизирован, чем generated RPC. gRPC подходит для внутренних low-latency contracts, GraphQL — для client-shaped queries, events — для asynchronous workflows.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Retry non-idempotent requests дублирует действия.
- Breaking changes representations без versioning ломают clients.
- Ответ 200 с embedded error разрушает HTTP semantics и observability.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Profiles приоритетов cloud connectors были доступны через REST API платформы; более широкое владение API не входило в заявленный scope кандидата.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает REST API?
Ответ: REST — architectural style вокруг resources, representations, uniform interface и stateless interactions. В практическом HTTP API поведение задают methods, status codes, headers, media types, caching и links.

2. Какие внутренние концепции важнее всего?
Ответ: Resource identifiers должны быть стабильными и не зависеть от операции. Safety и idempotency HTTP methods определяют retries и caching.

3. Что нужно явно определить в production design?
Ответ: Следует моделировать nouns, а не RPC verbs, валидировать inputs, согласовать pagination и errors, применять conditional requests и публиковать OpenAPI contract, если он принят командой.

4. Каков основной компромисс или альтернатива?
Ответ: REST/JSON доступен и browser-friendly, но verbose и слабее типизирован, чем generated RPC. gRPC подходит для внутренних low-latency contracts, GraphQL — для client-shaped queries, events — для asynchronous workflows.

5. Какой failure следует проверить первым?
Ответ: Retry non-idempotent requests дублирует действия. В контексте проекта: profiles приоритетов cloud connectors были доступны через REST API платформы; более широкое владение API не входило в заявленный scope кандидата.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm
- https://www.rfc-editor.org/rfc/rfc9110
