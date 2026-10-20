OpenTelemetry

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Наблюдаемость
Релевантный scope: Vendor-neutral metrics и traces через C++-сервисы, этапы FFmpeg и границы RPC.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

OpenTelemetry определяет APIs, SDKs, semantic conventions и протокол OTLP для traces, metrics и logs. Инструментированный код создаёт сигналы; SDK processors выполняют sampling и batching; collectors принимают, преобразуют и экспортируют данные.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Trace состоит из spans, связанных context propagation через границы процессов.
- Metrics используют instruments вроде counters и histograms с resource- и attribute-metadata.
- Collector отделяет instrumentation приложения от backend-specific exporters.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Context нужно передавать через gRPC metadata, задавать устойчивые low-cardinality attributes, sampling для частых spans и batch export вне hot path. Resource identity должна совпадать между deployments.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

OpenTelemetry снижает backend lock-in и связывает сигналы, но semantic conventions и sampling требуют управления. Прямая Prometheus instrumentation проще для metrics-only сервисов, provider agents удобнее, но менее переносимы.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Нарушенная context propagation фрагментирует traces.
- Чувствительные identifiers в attributes создают privacy risk.
- Always-on spans для каждого frame дают неприемлемые overhead и объём.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Кандидат спроектировал C++ telemetry interface, связал границы FFmpeg и очередей и использовал OpenTelemetry для событий одного segment, тогда как Prometheus и Google Cloud агрегировали метрики.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает OpenTelemetry?
Ответ: OpenTelemetry определяет APIs, SDKs, semantic conventions и протокол OTLP для traces, metrics и logs. Инструментированный код создаёт сигналы; SDK processors выполняют sampling и batching; collectors принимают, преобразуют и экспортируют данные.

2. Какие внутренние концепции важнее всего?
Ответ: Trace состоит из spans, связанных context propagation через границы процессов. Metrics используют instruments вроде counters и histograms с resource- и attribute-metadata.

3. Что нужно явно определить в production design?
Ответ: Context нужно передавать через gRPC metadata, задавать устойчивые low-cardinality attributes, sampling для частых spans и batch export вне hot path. Resource identity должна совпадать между deployments.

4. Каков основной компромисс или альтернатива?
Ответ: OpenTelemetry снижает backend lock-in и связывает сигналы, но semantic conventions и sampling требуют управления. Прямая Prometheus instrumentation проще для metrics-only сервисов, provider agents удобнее, но менее переносимы.

5. Какой failure следует проверить первым?
Ответ: Нарушенная context propagation фрагментирует traces. В контексте проекта: кандидат спроектировал C++ telemetry interface, связал границы FFmpeg и очередей и использовал OpenTelemetry для событий одного segment, тогда как Prometheus и Google Cloud агрегировали метрики.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://opentelemetry.io/docs/what-is-opentelemetry/
- https://opentelemetry.io/docs/compatibility/prometheus/
