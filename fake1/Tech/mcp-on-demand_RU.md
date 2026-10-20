mcp-on-demand

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: AI-инструменты
Релевантный scope: On-demand загрузка MCP servers, чтобы не держать definitions всех tools в каждой AI-session.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

mcp-on-demand — workflow запуска, вызова и остановки MCP servers только при необходимости. Лёгкий registry остаётся доступным, а полный server/tool schemas загружается для активной session.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- Lazy activation уменьшает baseline context и idle process cost.
- Session manager отслеживает active servers и маршрутизирует tool calls.
- Изоляция sessions ограничивает failure и позволяет restart.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Нужно регистрировать minimal descriptors, отдельно authorise server, запускать при первом реальном use, очищать idle sessions и явно показывать startup/tool failures. Lazy loading не должно обходить permission boundary.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

On-demand loading экономит context/resources при множестве specialist servers, но добавляет startup latency и lifecycle state. Always-on MCP проще для малого набора, built-in tools не требуют отдельного process.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Concurrent start requests могут создать duplicate sessions.
- Crash server оставляет stale session state.
- Dynamic tool loading без authorization раскрывает лишние capabilities.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

mcp-on-demand загружал полный code-index или metrics server при первом использовании, уменьшая unused tool context. Описанные incident workflows оставались read-only.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает mcp-on-demand?
Ответ: mcp-on-demand — workflow запуска, вызова и остановки MCP servers только при необходимости. Лёгкий registry остаётся доступным, а полный server/tool schemas загружается для активной session.

2. Какие внутренние концепции важнее всего?
Ответ: Lazy activation уменьшает baseline context и idle process cost. Session manager отслеживает active servers и маршрутизирует tool calls.

3. Что нужно явно определить в production design?
Ответ: Нужно регистрировать minimal descriptors, отдельно authorise server, запускать при первом реальном use, очищать idle sessions и явно показывать startup/tool failures. Lazy loading не должно обходить permission boundary.

4. Каков основной компромисс или альтернатива?
Ответ: On-demand loading экономит context/resources при множестве specialist servers, но добавляет startup latency и lifecycle state. Always-on MCP проще для малого набора, built-in tools не требуют отдельного process.

5. Какой failure следует проверить первым?
Ответ: Concurrent start requests могут создать duplicate sessions. В контексте проекта: mcp-on-demand загружал полный code-index или metrics server при первом использовании, уменьшая unused tool context. Описанные incident workflows оставались read-only.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://github.com/mfagerlund/mcp-on-demand
- https://modelcontextprotocol.io/docs/learn/architecture
