AWS: EC2, S3, Lambda и CloudFront

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Облака
Релевантный scope: Сервисы AWS объединены в один файл по flow; S3 был media-output destination, а EC2, Lambda и CloudFront названы в environment.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

AWS предоставляет infrastructure и managed services через regional APIs. EC2 даёт VM, S3 — object storage, Lambda — event-driven functions, CloudFront — global CDN/cache.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- S3 objects адресуются bucket/key; multipart upload помогает большим objects, но требует cleanup.
- EC2 capacity, networking и identity — явные infrastructure concerns.
- Lambda масштабирует invocations; CloudFront кэширует origin responses по cache key, TTL и invalidation.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Нужны least-privilege IAM, idempotent object keys, explicit timeouts, согласованные SDK/app retries и подтверждение перед manifest publication. Незавершённые multipart uploads следует abort, а throttling/cost — наблюдать.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

AWS даёт широкую зрелую экосистему и global reach. Costs, quotas и provider semantics требуют проектирования. Azure и Google Cloud предлагают аналоги; portability layer уменьшает coupling, но не устраняет различия.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Timeout оставляет ambiguous write outcome.
- Незавершённые multipart uploads потребляют storage/operations.
- SDK и application retries вместе усиливают throttling.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Кандидат бенчмаркировал profiles S3-коннектора, улучшал segment-deadline reliability и реализовал recovery с bounded local queues, idempotent keys, existence checks и ordered catch-up. EC2, Lambda и CloudFront указаны без дополнительных личных claims.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает AWS: EC2, S3, Lambda и CloudFront?
Ответ: AWS предоставляет infrastructure и managed services через regional APIs. EC2 даёт VM, S3 — object storage, Lambda — event-driven functions, CloudFront — global CDN/cache.

2. Какие внутренние концепции важнее всего?
Ответ: S3 objects адресуются bucket/key; multipart upload помогает большим objects, но требует cleanup. EC2 capacity, networking и identity — явные infrastructure concerns.

3. Что нужно явно определить в production design?
Ответ: Нужны least-privilege IAM, idempotent object keys, explicit timeouts, согласованные SDK/app retries и подтверждение перед manifest publication. Незавершённые multipart uploads следует abort, а throttling/cost — наблюдать.

4. Каков основной компромисс или альтернатива?
Ответ: AWS даёт широкую зрелую экосистему и global reach. Costs, quotas и provider semantics требуют проектирования. Azure и Google Cloud предлагают аналоги; portability layer уменьшает coupling, но не устраняет различия.

5. Какой failure следует проверить первым?
Ответ: Timeout оставляет ambiguous write outcome. В контексте проекта: кандидат бенчмаркировал profiles S3-коннектора, улучшал segment-deadline reliability и реализовал recovery с bounded local queues, idempotent keys, existence checks и ordered catch-up. EC2, Lambda и CloudFront указаны без дополнительных личных claims.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html
- https://docs.aws.amazon.com/ec2/
- https://docs.aws.amazon.com/lambda/
- https://docs.aws.amazon.com/cloudfront/
