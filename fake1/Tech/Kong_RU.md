Kong Gateway

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Сети и протоколы
Релевантный scope: API gateway, указанный в широком окружении микросервисной платформы.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

Kong Gateway — reverse proxy и API gateway, который направляет client traffic к upstream services и применяет plugins для authentication, rate limiting, transformation и observability.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Routes сопоставляют incoming requests и направляют их к Services/upstream targets.
- Plugins могут работать global или в scoped entities, поэтому важны scope и order.
- Declarative и database-backed modes дают разные configuration workflows.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Gateway policy должна быть тонкой; configuration — versioned; admin API — с least privilege. Нужно тестировать взаимодействие timeout/retry с clients и безопасно сохранять trace context и request identity.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

API gateway централизует cross-cutting controls, но может стать bottleneck и policy monolith. Cloud gateways уменьшают operations, service mesh работает с east-west traffic, direct ingress проще для малых систем.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Gateway retries могут умножать application retries.
- Публично доступный admin API — критическая уязвимость.
- Transformations, расходящиеся с service contracts, усложняют debug.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Kong входил в окружение проекта; configuration и operations Kong не входили в заявленный scope кандидата.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает Kong Gateway?
Ответ: Kong Gateway — reverse proxy и API gateway, который направляет client traffic к upstream services и применяет plugins для authentication, rate limiting, transformation и observability.

2. Какие внутренние концепции важнее всего?
Ответ: Routes сопоставляют incoming requests и направляют их к Services/upstream targets. Plugins могут работать global или в scoped entities, поэтому важны scope и order.

3. Что нужно явно определить в production design?
Ответ: Gateway policy должна быть тонкой; configuration — versioned; admin API — с least privilege. Нужно тестировать взаимодействие timeout/retry с clients и безопасно сохранять trace context и request identity.

4. Каков основной компромисс или альтернатива?
Ответ: API gateway централизует cross-cutting controls, но может стать bottleneck и policy monolith. Cloud gateways уменьшают operations, service mesh работает с east-west traffic, direct ingress проще для малых систем.

5. Какой failure следует проверить первым?
Ответ: Gateway retries могут умножать application retries. В контексте проекта: kong входил в окружение проекта; configuration и operations Kong не входили в заявленный scope кандидата.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://developer.konghq.com/gateway/
- https://developer.konghq.com/gateway/entities/
