Google Cloud: Compute Engine, Cloud Storage, Cloud Functions и Monitoring

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Облака
Релевантный scope: Сервисы Google Cloud объединены в один provider-файл; Cloud Storage и Monitoring явно участвовали в output и observability.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

Google Cloud предоставляет regional/global managed services. Compute Engine даёт VM, Cloud Storage хранит immutable object generations, Cloud Functions выполняет event-driven code, Cloud Monitoring хранит telemetry и alerts.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Cloud Storage generations и preconditions поддерживают безопасные conditional writes.
- Application Default Credentials и workload identity уменьшают распространение static keys.
- Cloud Monitoring metrics используют monitored resources и labels, cardinality которых нужно ограничивать.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Нужно использовать generation preconditions для idempotency, explicit deadlines/classified retries и подтверждать object до manifest publication. Resource labels OpenTelemetry и provider dashboards должны совпадать.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

Google Cloud объединяет infrastructure, object storage, serverless и monitoring. Provider-specific identity, quotas и metric schemas сохраняются. AWS/Azure — альтернативы; portable APIs всё равно требуют adapters.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Unbounded object listing и high-cardinality metrics увеличивают cost.
- Retry без preconditions может overwrite/duplicate state.
- Credential expiry должен запускать refresh, а не бесконечный backoff.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Кандидат бенчмаркировал и восстанавливал output в Google Cloud Storage; Google Cloud Monitoring агрегировал encoder/stage metrics вместе с Prometheus/OpenTelemetry. Compute Engine и Cloud Functions указаны без дополнительных claims.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает Google Cloud: Compute Engine, Cloud Storage, Cloud Functions и Monitoring?
Ответ: Google Cloud предоставляет regional/global managed services. Compute Engine даёт VM, Cloud Storage хранит immutable object generations, Cloud Functions выполняет event-driven code, Cloud Monitoring хранит telemetry и alerts.

2. Какие внутренние концепции важнее всего?
Ответ: Cloud Storage generations и preconditions поддерживают безопасные conditional writes. Application Default Credentials и workload identity уменьшают распространение static keys.

3. Что нужно явно определить в production design?
Ответ: Нужно использовать generation preconditions для idempotency, explicit deadlines/classified retries и подтверждать object до manifest publication. Resource labels OpenTelemetry и provider dashboards должны совпадать.

4. Каков основной компромисс или альтернатива?
Ответ: Google Cloud объединяет infrastructure, object storage, serverless и monitoring. Provider-specific identity, quotas и metric schemas сохраняются. AWS/Azure — альтернативы; portable APIs всё равно требуют adapters.

5. Какой failure следует проверить первым?
Ответ: Unbounded object listing и high-cardinality metrics увеличивают cost. В контексте проекта: кандидат бенчмаркировал и восстанавливал output в Google Cloud Storage; Google Cloud Monitoring агрегировал encoder/stage metrics вместе с Prometheus/OpenTelemetry. Compute Engine и Cloud Functions указаны без дополнительных claims.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://cloud.google.com/storage/docs
- https://cloud.google.com/compute/docs
- https://cloud.google.com/functions/docs
- https://cloud.google.com/monitoring/docs
