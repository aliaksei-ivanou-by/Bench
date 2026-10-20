FFmpeg, libavfilter, libavformat и libav

1. ПРОФИЛЬ ТЕХНОЛОГИИ

Категория: Медиа
Релевантный scope: Библиотеки FFmpeg в live/VOD медиаконвейере; libavfilter, libavformat и семейство libav объединены как компоненты одного проекта FFmpeg.

2. ЧТО ЭТО И КАКУЮ ЗАДАЧУ РЕШАЕТ

FFmpeg — мультимедийный framework с CLI и библиотеками для demux, decode, filter, encode и mux. libavformat работает с containers и protocols; libavfilter выполняет filter graphs; timestamps и time bases связывают этапы.

3. КЛЮЧЕВЫЕ КОНЦЕПЦИИ И ВНУТРЕННЯЯ МОДЕЛЬ

- AVPacket представляет compressed data, AVFrame — decoded audio/video.
- У каждого stream и link свой rational time base; PTS и DTS нужно явно rescale.
- Filter graph — направленный граф sources, filters, links и sinks с согласованием formats.

На интервью важно не только знать термины. Сильный ответ связывает абстракцию с lifecycle, failure semantics, владением данными и границей гарантий технологии.

4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Нужно разделять владение packets/frames, drain codecs и filters при EOS, нормализовать timestamps на определённых границах и измерять processing и queue time. Проверять надо timestamps и media output, а не только успешные API calls.

Практический workflow: versioned configuration, наблюдаемые inputs/outputs, преднамеренная проверка failure path и достаточная диагностика для воспроизведения результата вне production.

5. СИЛЬНЫЕ СТОРОНЫ, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

FFmpeg даёт широкую поддержку форматов и высокую производительность, но имеет сложный stateful API и version-sensitive behavior. GStreamer предлагает компонентную pipeline model, platform media frameworks упрощают узкие deployments.

Выбор определяется не популярностью, а workload и operational constraints: latency, throughput, consistency, portability, ownership команды и требования recovery.

6. ТИПИЧНЫЕ ОШИБКИ, ПРОИЗВОДИТЕЛЬНОСТЬ И БЕЗОПАСНОСТЬ

- Неверное преобразование time base вызывает drift и расхождение manifests.
- Лишние очереди и temporal filters добавляют latency.
- Пропуск flush/drain теряет задержанные frames на переходах.

Performance claim требует определённого workload, warm-up policy, percentile или deadline target и неизменной correctness baseline. Security claim требует явных identity, authorization, secret handling и provenance зависимостей.

7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТЕ КАНДИДАТА

Проект: Cloud Native Encoding Platform, апрель 2025 – настоящее время.

Кандидат инструментировал libavfilter и границы очередей, обнаружил лишнее накопление frames и ненужный copy/synchronization step и снизил end-to-end latency на четыре секунды. Caption data извлекались через FFmpeg frame/format APIs.

8. ВЕРОЯТНЫЕ ВОПРОСЫ НА ИНТЕРВЬЮ

1. Какую задачу здесь решает FFmpeg, libavfilter, libavformat и libav?
Ответ: FFmpeg — мультимедийный framework с CLI и библиотеками для demux, decode, filter, encode и mux. libavformat работает с containers и protocols; libavfilter выполняет filter graphs; timestamps и time bases связывают этапы.

2. Какие внутренние концепции важнее всего?
Ответ: AVPacket представляет compressed data, AVFrame — decoded audio/video. У каждого stream и link свой rational time base; PTS и DTS нужно явно rescale.

3. Что нужно явно определить в production design?
Ответ: Нужно разделять владение packets/frames, drain codecs и filters при EOS, нормализовать timestamps на определённых границах и измерять processing и queue time. Проверять надо timestamps и media output, а не только успешные API calls.

4. Каков основной компромисс или альтернатива?
Ответ: FFmpeg даёт широкую поддержку форматов и высокую производительность, но имеет сложный stateful API и version-sensitive behavior. GStreamer предлагает компонентную pipeline model, platform media frameworks упрощают узкие deployments.

5. Какой failure следует проверить первым?
Ответ: Неверное преобразование time base вызывает drift и расхождение manifests. В контексте проекта: кандидат инструментировал libavfilter и границы очередей, обнаружил лишнее накопление frames и ненужный copy/synchronization step и снизил end-to-end latency на четыре секунды. Caption data извлекались через FFmpeg frame/format APIs.

9. ИСТОЧНИКИ

Дата исследования: 2026-10-20.

- https://www.ffmpeg.org/documentation.html
- https://ffmpeg.org/ffmpeg-filters.html
- https://ffmpeg.org/libavfilter.html
