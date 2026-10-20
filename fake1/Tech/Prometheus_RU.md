Prometheus

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Наблюдаемость
Релевантный scope: Сбор и запрос метрик C++-кодировщика, очередей, RPC и облачных выходов.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

Prometheus — pull-oriented monitoring system с многомерной моделью time series. Sample определяется именем метрики и набором labels; PromQL вычисляет rates, aggregations и alerts.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Counters растут до reset; gauges изменяются в обе стороны; histograms распределяют наблюдения по buckets.
- Scraping отделяет instrumentation от storage и показывает health targets.
- Recording rules заранее считают дорогие expressions, alert rules проверяют условия во времени.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Метрики следует называть по наблюдаемому поведению, явно задавать units, ограничивать labels и выбирать buckets по реальным SLO. Для counters считаются rates, а histogram buckets агрегируются с сохранением label le.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

Prometheus имеет простую модель и сильный query language, но не является общим event store, а высокая cardinality дорога. OpenTelemetry даёт vendor-neutral instrumentation, managed monitoring снижает операционную нагрузку.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- User IDs, filenames и segment IDs в labels вызывают cardinality explosion.
- Counters без rate window вводят в заблуждение.
- Телеметрия в hot path может исказить измеряемую систему.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Prometheus агрегировал метрики кодировщика, stage latency и распределение успеха по deadline вместе с sampled OpenTelemetry traces и Grafana dashboards.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает Prometheus?
Ответ: Prometheus — pull-oriented monitoring system с многомерной моделью time series. Sample определяется именем метрики и набором labels; PromQL вычисляет rates, aggregations и alerts.

2. Какие внутренние концепции важнее всего?
Ответ: Counters растут до reset; gauges изменяются в обе стороны; histograms распределяют наблюдения по buckets. Scraping отделяет instrumentation от storage и показывает health targets.

3. Что нужно явно определить в production design?
Ответ: Метрики следует называть по наблюдаемому поведению, явно задавать units, ограничивать labels и выбирать buckets по реальным SLO. Для counters считаются rates, а histogram buckets агрегируются с сохранением label le.

4. Каков основной компромисс или альтернатива?
Ответ: Prometheus имеет простую модель и сильный query language, но не является общим event store, а высокая cardinality дорога. OpenTelemetry даёт vendor-neutral instrumentation, managed monitoring снижает операционную нагрузку.

5. Какой failure следует проверить первым?
Ответ: User IDs, filenames и segment IDs в labels вызывают cardinality explosion. В контексте проекта: prometheus агрегировал метрики кодировщика, stage latency и распределение успеха по deadline вместе с sampled OpenTelemetry traces и Grafana dashboards.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://prometheus.io/docs/introduction/overview/
- https://prometheus.io/docs/practices/instrumentation/
