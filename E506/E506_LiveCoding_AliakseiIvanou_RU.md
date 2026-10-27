ИНФОРМАЦИЯ О ДОКУМЕНТЕ

Идентификатор запроса: E506
Кандидат: Alex I.
Целевая роль: Senior C++ Engineer / Hands-on Technical Lead
Артефакт: Подготовка к live coding
Язык: Русский
Источник: запрос E506 и предоставленная кандидатом гипотеза о формате интервью

ЦЕЛЬ

Документ готовит повторяемый шестидесятиминутный flow live coding на C++ для автомобильной задачи, основанной на требованиях. Ожидаемая задача, скорее всего, будет не алгоритмической головоломкой, а небольшой моделью процесса с явными интерфейсами, GoogleTest и GoogleMock, негативным поведением, обработкой отказов и трассировкой от согласованной спецификации до тестов и реализации.

ПАПКИ С ПРАКТИЧЕСКИМИ УПРАЖНЕНИЯМИ

Шесть самостоятельных упражнений с пошаговыми требованиями, моками, тестами, рекомендациями по реализации и границами верификации перечислены в LiveCoding/README_RU.md. Каждая папка содержит синхронизированные README на английском и русском языках и может независимо использоваться как пробное интервью с ограничением по времени.

ГРАНИЦА ОПЫТА

ISO 26262 и ASIL в этом файле являются темами подготовки, а не заявлением о прямом проектном опыте кандидата. Готовая позиция для интервью: я работал в формальной safety-oriented разработке аэрокосмических систем и с верификацией на основе требований, но не работал на production-проекте под управлением ISO 26262. На live coding я могу следовать предоставленному V-model и safety-процессу, явно фиксировать предположения и выводить код и тесты из согласованных требований.

Текущая опубликованная базовая версия ISO — редакция 2018 года. Третья редакция находится в разработке, поэтому фактическая базовая версия и правила tailoring заказчика имеют приоритет.

ПРЕДПОЛАГАЕМЫЙ FLOW НА ШЕСТЬДЕСЯТ МИНУТ

Минуты 0–5: Понять item и наблюдаемое поведение

- Переформулировать задачу одним предложением.
- Определить границу системы, вызывающую сторону, зависимости и actuator или выход.
- Спросить, какая malfunction является safety-relevant и каково безопасное состояние.
- Уточнить единицы, допустимые диапазоны, timing, freshness и поведение reset.
- Уточнить, является ли компонент циклическим, event-driven или сочетает оба режима.
- Уточнить, разрешены ли dynamic allocation, exceptions, threads и blocking calls.
- Спросить, назначены ли уже ASIL и safety requirements или ожидается учебное обсуждение HARA.
- Записать нерешённые вопросы как явные предположения. Не придумывать поведение молча.

Минуты 5–10: Написать компактную спецификацию

- Дать каждому требованию устойчивый идентификатор, например REQ-AEB-001.
- Определить входы, выходы, предусловия и инварианты.
- Определить штатное, граничное, недопустимое, устаревшее поведение и реакцию на отказ зависимости.
- Определить безопасное состояние и условия восстановления.
- Определить, какие side effects должны происходить один раз, могут повторяться или не должны происходить никогда.
- Получить устное согласование до написания кода.

Минуты 10–15: Определить интерфейсы и test seams

- Сделать decision logic небольшой и детерминированной.
- Инъецировать время, сенсоры, actuators, диагностику и transport через интерфейсы.
- Мокировать внешние границы, а не value objects или приватные детали реализации.
- Предпочитать явные result types и status values скрытому глобальному состоянию.
- Делать единицы заметными в именах или strong types.

Минуты 15–30: Сначала написать тесты

- Начать с одного позитивного теста требования.
- Добавить boundary tests на точных порогах.
- Добавить тесты недопустимых, отсутствующих и устаревших входов.
- Добавить отказ зависимости и проверку safe state.
- Добавить временные тесты для debounce, timeout, hysteresis или повторных вызовов.
- Проверить обязательные взаимодействия и запрещённые вызовы actuator.
- Связать каждый тест хотя бы с одним идентификатором требования.

Минуты 30–45: Реализовать минимальное согласованное поведение

- Реализовать только поведение, обоснованное согласованными требованиями.
- Сделать валидацию и переходы состояний явными.
- Не добавлять предположительные абстракции и лишние возможности.
- Запускать suite после каждого небольшого изменения.
- Выполнять refactoring только при зелёных тестах.

Минуты 45–55: Усилить evidence

- Просмотреть непокрытые branches и объяснить достижимость каждой.
- Добавить отсутствующие негативные и граничные случаи.
- Проверить повторное выполнение, идемпотентность и reset.
- Проверить numeric overflow, NaN, invalid enums и порядок или wrap timestamps, если это релевантно.
- Объяснить, что unit tests доказать не могут и какой integration или target test даст следующий уровень evidence.

Минуты 55–60: Замкнуть V-model

- Сопоставить каждое требование с тестами и реализацией.
- Подвести итог по safe-state поведению и оставшимся предположениям.
- Назвать следующие integration и system tests.
- Упомянуть review, static analysis, compiler warnings и coverage evidence.
- Для safety-related item объяснить, что ASIL происходит из HARA и распределённых safety requirements, а не из самого класса C++.

ЧТО ГОВОРИТЬ ВО ВРЕМЯ РАБОТЫ

- Before I write code, I want to agree on the observable contract.
- I do not want to guess the safe state. What should the component command when an input is missing or stale?
- I will write this as REQ-003 so the test name and implementation decision are traceable.
- I am mocking time because freshness is part of the behavior, not because the clock implementation is interesting.
- This test proves the unit contract. A real actuator, scheduler or bus still requires integration and target-level evidence.
- Line coverage is useful for finding gaps, but requirements and decision coverage matter more than reaching an arbitrary percentage.
- I am not adding that branch because no approved requirement defines the behavior.

ОТОБРАЖЕНИЕ V-MODEL НА LIVE CODING

Левая сторона, декомпозиция:

- Item и hazardous event: предоставлены интервьюером или обсуждены как предположение.
- Safety goal: высокоуровневое утверждение, предотвращающее или контролирующее опасное поведение.
- Functional и technical safety requirement: требуемое поведение и safe state.
- Software safety requirement: наблюдаемый контракт компонента.
- Interface и detailed design: типы C++, ports, состояния и алгоритмы.

Нижняя точка:

- Реализация по coding rules проекта, с включёнными warnings и без необоснованного поведения.

Правая сторона, verification и validation:

- Unit tests проверяют детальные решения, диапазоны и переходы состояний.
- Component tests проверяют компонент через mocked или simulated boundaries.
- Integration tests проверяют реальные интерфейсы, scheduling, serialization и поведение зависимостей.
- Target tests проверяют timing, hardware, drivers и фактическую среду выполнения.
- System validation проверяет, что реализованный item удовлетворяет safety goal в репрезентативных дорожных ситуациях.

Live-coding упражнение может продемонстрировать части цепочки, относящиеся к software requirements, unit и component. Само по себе оно не доказывает безопасность на уровне автомобиля.

ОБСУЖДЕНИЕ ISO 26262 И ASIL

ASIL классифицирует hazardous event на уровне item. Класс выводится во время hazard analysis and risk assessment из:

- Severity: потенциальный вред при возникновении hazardous event.
- Exposure: частота соответствующей эксплуатационной ситуации.
- Controllability: вероятность того, что водитель или другие участники движения смогут избежать вреда.

Результатом может быть QM или ASIL A, B, C либо D. ASIL D — самый высокий integrity level в этой шкале. Затем класс распределяется через safety goals и safety requirements. Класс software сам по себе не становится ASIL D только потому, что в его названии есть brake или steering.

Flow упражнения на ASIL:

1. Определить item и функцию на уровне автомобиля.
2. Назвать malfunctioning behavior, а не только отказ компонента.
3. Объединить её с конкретной эксплуатационной ситуацией.
4. Описать hazardous event и возможный вред.
5. Обсудить Severity, Exposure и Controllability с явными предположениями.
6. По предоставленной заказчиком таблице классификации получить предварительный ASIL.
7. Сформулировать safety goal.
8. Вывести software requirement и способ его верификации.

Учебное предположение высокой критичности:

- Item: automatic emergency braking.
- Malfunctioning behavior: максимальное торможение без достоверного препятствия.
- Эксплуатационная ситуация: движение по автомагистрали на высокой скорости при наличии транспорта сзади.
- Учебные предположения интервьюера: S3, E4 и C3.
- Предварительный учебный результат: ASIL D.
- Пример safety goal: непреднамеренное экстренное торможение должно предотвращаться или контролироваться так, чтобы автомобиль не создавал неприемлемый риск столкновения.

Учебный контраст с QM:

- Item: декоративное ambient lighting в салоне.
- Malfunctioning behavior: выбранный цвет не применяется.
- При заданных эксплуатационных предположениях safety-relevant вред не выявлен.
- Учебный результат: QM, при этом обычные требования к качеству сохраняются.

Нельзя запоминать ASIL без сценария. Одна и та же функция может создавать разные hazardous events и классы при разных предположениях о скорости, трафике, контроле водителя и exposure.

ПОВТОРНО ИСПОЛЬЗУЕМЫЙ ШАБЛОН СПЕЦИФИКАЦИИ

Постановка задачи:

- Ответственность компонента.
- Внешние входы и выходы.
- Execution model.

Согласованные с интервьюером предположения:

- Единицы и допустимые диапазоны.
- Timing и freshness.
- Safe state.
- Recovery и reset.
- Политика error reporting.
- Ограничения на allocation и exceptions.

Требования:

- REQ-001: Позитивное поведение.
- REQ-002: Граничное поведение.
- REQ-003: Недопустимый или отсутствующий вход.
- REQ-004: Timeout или stale data.
- REQ-005: Отказ зависимости.
- REQ-006: Повтор, идемпотентность или переход состояния.

Матрица тестов:

- Один обычный позитивный случай.
- Точные нижняя и верхняя границы.
- Значения непосредственно ниже и выше каждого порога.
- Отсутствующий вход.
- Invalid enum, NaN, infinity или число вне диапазона, если применимо.
- Устаревший timestamp.
- Зависимость возвращает ошибку или выбрасывает исключение, если exceptions входят в контракт.
- Повторное событие или повторный tick.
- Восстановление после исчезновения неисправности.
- Запрещённое взаимодействие с actuator.

Закрытие traceability:

- Идентификатор требования.
- Имена тестов.
- Функция реализации или переход состояния.
- Следующее integration или target-level evidence.

ГРАНИЦЫ МОКИРОВАНИЯ

Хорошие кандидаты для mock:

- Clock или monotonic time source.
- Sensor или perception input port.
- Actuator command port.
- Diagnostic-event sink.
- Persistent state или transport boundary.
- Scheduler callback, когда timing входит в контракт.

Не следует мокировать по умолчанию:

- Простые value objects.
- Чистые функции вычисления.
- Стандартные контейнеры.
- Приватные методы.
- Каждый внутренний collaborator только ради количества mocks.

Mock должен делать внешний контракт управляемым или наблюдаемым. Избыточная проверка взаимодействий усложняет refactoring и может тестировать порядок реализации вместо требуемого поведения.

ПОЛНОСТЬЮ РАЗОБРАННОЕ УПРАЖНЕНИЕ 1 — AUTOMATIC EMERGENCY BRAKING REQUEST GATE

Постановка

Реализовать циклический компонент C++, который читает последний perception sample и решает, нужно ли отправлять запрос экстренного торможения. Использовать GoogleTest и GoogleMock. Компонент никогда не должен запрашивать торможение по недопустимым или устаревшим данным.

Вопросы до начала кодирования

- Какие пороги скорости, confidence и time to collision применяются?
- Включают ли пороги точное граничное значение?
- Когда sample считается устаревшим?
- Каково безопасное поведение для отсутствующих, malformed или stale данных?
- Подавляет ли driver override запрос торможения?
- Должен ли повторный tick повторно отправлять ту же команду?
- Как сообщается об отказе actuator?
- Разрешены ли exceptions и dynamic allocation в cyclic path?
- Требуются ли hysteresis или debounce?
- Какие ASIL и safety requirement распределены на этот компонент?

Согласованные с интервьюером предположения для учебной версии

- Метод tick() вызывается каждые десять миллисекунд.
- Экстренное торможение разрешено при скорости не менее 5,0 m/s, confidence не менее 0,90 и time to collision не более 1,20 секунды.
- Sample старше 100 миллисекунд считается stale.
- Driver override подавляет запрос.
- Отсутствующие, non-finite, выходящие за диапазон или stale данные не создают запрос торможения и формируют одно диагностическое событие за tick.
- Desired deceleration приходит от perception, должна быть finite и ограничивается диапазоном от 0,0 до 8,0 m/s².
- Каждый допустимый hazardous sample создаёт один запрос actuator. Идемпотентность между ticks не входит в эту версию, если интервьюер её не добавит.
- Если actuator отклоняет запрос, компонент сообщает ActuatorRejected.

Требования

- REQ-AEB-001: Fresh hazardous sample, удовлетворяющий всем включительным порогам и не имеющий driver override, должен создать один ограниченный запрос торможения.
- REQ-AEB-002: Non-hazardous sample не должен создавать запрос торможения.
- REQ-AEB-003: Driver override должен подавлять запрос торможения.
- REQ-AEB-004: Отсутствующий или stale input не должен создавать запрос и должен сообщать соответствующую диагностику.
- REQ-AEB-005: NaN, infinity или значения вне согласованных физических диапазонов не должны создавать запрос и должны сообщать InvalidSample.
- REQ-AEB-006: Desired deceleration выше 8,0 m/s² должна ограничиваться значением 8,0 m/s².
- REQ-AEB-007: Отказ actuator должен сообщать ActuatorRejected.

Предлагаемые интерфейсы

    using Milliseconds = std::chrono::milliseconds;
    using TimePoint = std::chrono::steady_clock::time_point;

    struct PerceptionSample {
        double vehicleSpeedMps;
        double confidence;
        double timeToCollisionSec;
        double desiredDecelerationMps2;
        bool driverOverride;
        TimePoint timestamp;
    };

    enum class Fault {
        MissingSample,
        StaleSample,
        InvalidSample,
        ActuatorRejected
    };

    class IPerceptionPort {
    public:
        virtual ~IPerceptionPort() = default;
        virtual std::optional<PerceptionSample> latest() = 0;
    };

    class IClock {
    public:
        virtual ~IClock() = default;
        virtual TimePoint now() const = 0;
    };

    class IBrakePort {
    public:
        virtual ~IBrakePort() = default;
        virtual bool request(double decelerationMps2) = 0;
    };

    class IDiagnostics {
    public:
        virtual ~IDiagnostics() = default;
        virtual void report(Fault fault) = 0;
    };

    class AebRequestGate {
    public:
        AebRequestGate(IPerceptionPort&, IClock&, IBrakePort&, IDiagnostics&);
        void tick();
    };

Порядок тестов

1. REQ-AEB-001 — запрос торможения для обычного hazardous sample.
2. REQ-AEB-001 — значения точно на всех трёх порогах принимаются.
3. REQ-AEB-002 — запроса нет при confidence непосредственно ниже 0,90.
4. REQ-AEB-002 — запроса нет при time to collision непосредственно выше 1,20.
5. REQ-AEB-002 — запроса нет при скорости непосредственно ниже 5,0.
6. REQ-AEB-003 — driver override запрещает взаимодействие с actuator.
7. REQ-AEB-004 — отсутствующий sample сообщает MissingSample и запрещает взаимодействие с actuator.
8. REQ-AEB-004 — sample возрастом ровно 100 миллисекунд принимается, более старый считается stale.
9. REQ-AEB-005 — параметризованные invalid inputs покрывают NaN, infinity, отрицательную скорость, confidence вне диапазона от нуля до единицы и неположительный time to collision.
10. REQ-AEB-006 — избыточная deceleration ограничивается значением 8,0.
11. REQ-AEB-007 — отказ actuator создаёт диагностическое событие.

Репрезентативные expectations GoogleMock

    EXPECT_CALL(perception, latest())
        .WillOnce(Return(validHazardousSample));
    EXPECT_CALL(clock, now())
        .WillOnce(Return(now));
    EXPECT_CALL(brake, request(DoubleEq(4.0)))
        .WillOnce(Return(true));
    EXPECT_CALL(diagnostics, report(_)).Times(0);

Для недопустимого входа:

    EXPECT_CALL(perception, latest())
        .WillOnce(Return(invalidSample));
    EXPECT_CALL(brake, request(_)).Times(0);
    EXPECT_CALL(diagnostics, report(Fault::InvalidSample));

Порядок реализации

- Прочитать sample один раз.
- Обработать отсутствие input.
- Прочитать clock один раз и проверить freshness.
- Проверить каждое числовое поле через std::isfinite и согласованные диапазоны.
- Применить driver override и hazard thresholds.
- Ограничить requested deceleration.
- Один раз вызвать actuator.
- При необходимости сообщить об отказе.

Обсуждение ASIL

Gate не назначает себе ASIL. Нужно начать с двух отдельных malfunctioning behaviors: непреднамеренное торможение и отсутствие запроса торможения. Для учебного сценария максимального непреднамеренного торможения на автомагистрали интервьюер задаёт S3, E4 и C3, что даёт предварительное упражнение ASIL D. Соответствующие software requirements, ожидания независимости и строгость верификации происходят из распределённого safety-процесса. Приведённые unit tests являются необходимым evidence, но недостаточны для validation на уровне автомобиля.

V-model evidence за пределами unit test

- Component test с реальным сериализованным perception message.
- Integration test с transport тормозной команды и diagnostic manager.
- Timing test под target scheduler.
- Fault injection для stale, delayed, malformed и duplicated messages.
- Vehicle или HIL validation торможения и driver-override поведения.
- Trace links от safety requirement до тестов, code review, coverage и результатов.

УПРАЖНЕНИЕ 2 — МОНИТОР ДОСТОВЕРНОСТИ ДВУХ ДАТЧИКОВ СКОРОСТИ КОЛЕСА

Постановка

Смоделировать циклический монитор, получающий основное и резервное значения скорости колеса. Расхождение выше порога в течение трёх последовательных циклов должно переводить компонент в состояние Degraded. Пять последовательных согласованных циклов должны восстанавливать Available. Отсутствующие, stale или non-finite данные должны немедленно переводить компонент в Degraded.

Необходимые mocks

- Два sensor ports.
- Monotonic clock.
- Diagnostic sink.
- Availability output port.

Важные тесты

- Оба значения равны и допустимы.
- Разница точно на пороге.
- Разница непосредственно выше порога в течение одного, двух и трёх циклов.
- Сброс счётчика, когда один согласованный цикл прерывает последовательность.
- Немедленная деградация для отсутствующего значения, stale, NaN или infinity.
- Восстановление только после ровно пяти последовательных согласованных циклов.
- Отсутствие повторного availability notification, если состояние не изменилось.

Обсуждение ASIL

Нужно спросить, какая функция автомобиля использует скорость и какой hazardous event создаёт неправильное значение. Значение только для дисплея и значение для braking или stability control не получают одинаковую классификацию. Нельзя назначать ASIL до определения эксплуатационной ситуации и предположений S, E и C.

УПРАЖНЕНИЕ 3 — ОГРАНИЧИТЕЛЬ КОМАНДЫ РУЛЕВОГО УПРАВЛЕНИЯ

Постановка

Реализовать компонент, принимающий requested steering torque и выдающий ограниченную команду. Он должен обеспечивать абсолютный предел torque и ограничение скорости изменения, отклонять stale и non-finite requests и подавлять assistance при активном driver override.

Необходимые mocks

- Command input port.
- Clock.
- Steering actuator.
- Diagnostic sink.

Важные тесты

- Обычная команда внутри обоих ограничений.
- Точные положительная и отрицательная границы torque.
- Положительная и отрицательная rate limit с управляемым временем.
- Нулевое или отрицательное elapsed time.
- NaN и infinity.
- Stale command.
- Driver override.
- Отказ actuator.
- Обновление состояния только после принятой команды.

Обсуждение ASIL

Непреднамеренное рулевое воздействие на скорости может создавать hazardous event высокой severity, но классификация всё равно зависит от item, эксплуатационной ситуации, exposure и controllability. Нужно спросить, является ли safe reaction нулевой torque, управляемым ramp-down или передачей управления другому controller; нельзя придумывать её самостоятельно.

УПРАЖНЕНИЕ 4 — SUPERVISOR ТЕПЛОВОЙ ЗАЩИТЫ БАТАРЕИ

Постановка

Реализовать небольшой state machine с состояниями Normal, CoolingRequested и ShutdownRequested. Он читает два температурных датчика, проверяет plausibility, применяет hysteresis и управляет охлаждением или shutdown через mocked ports.

Необходимые mocks

- Два temperature sensors.
- Clock или cycle source.
- Cooling actuator.
- Shutdown request port.
- Diagnostic sink.

Важные тесты

- Нормальная работа ниже порога охлаждения.
- Охлаждение начинается точно на пороге.
- Hysteresis предотвращает быстрое переключение.
- Shutdown начинается на критическом пороге.
- Расхождение датчиков.
- Отказ одного датчика и отказ обоих датчиков.
- Stale и non-finite values.
- Отказ actuator и safe-state поведение.
- Правила восстановления после снижения температуры.

Обсуждение ASIL

Следует разделять номинальную защиту от перегрева и malfunctioning E/E behavior. Нужно спросить, какой вред может создать software malfunction, насколько часто возникает соответствующая ситуация движения или зарядки и может ли водитель её контролировать. Класс нельзя вывести только из слова battery.

УПРАЖНЕНИЕ 5 — КООРДИНАТОР ПРЕДУПРЕЖДЕНИЙ PARKING ASSIST

Постановка

Объединить обновления расстояния от четырёх сенсоров и выдавать ближайшую допустимую зону препятствия. Входы истекают по timeout. Недопустимые сенсоры исключаются, но компонент должен сообщать о degraded coverage и не должен показывать безопасное расстояние, если все сенсоры недопустимы.

Необходимые mocks

- Четыре sensor ports или один индексируемый sensor interface.
- Clock.
- Warning-output port.
- Diagnostic sink.

Важные тесты

- Выбор ближайшего допустимого препятствия.
- Точные границы зон.
- Один invalid sensor при наличии оставшегося покрытия.
- Все сенсоры недопустимы.
- Stale data.
- Out-of-order timestamps.
- Duplicate samples.
- Warning меняется только при изменении наблюдаемой зоны.
- Восстановление одного сенсора после деградации.

Обсуждение ASIL

ASIL зависит от того, является ли это advisory parking assistance или входом для автоматического движения автомобиля. Нужно спросить, кто сохраняет управление, какова максимальная скорость и как определена safe reaction. Одна и та же sensor logic может быть QM в одном item и safety-related в другом.

УПРАЖНЕНИЕ 6 — КОНТРОЛЛЕР AMBIENT LIGHT В САЛОНЕ КАК КОНТРАСТ С QM

Постановка

Реализовать controller, который выбирает запрошенный цвет освещения салона, переходит к цвету по умолчанию для неподдерживаемых значений и сохраняет последнюю принятую настройку. Использовать mocks для light driver и persistence.

Необходимые mocks

- Light-driver port.
- Preference store.
- Diagnostic или logging sink, если этого требует спецификация.

Важные тесты

- Поддерживаемый цвет.
- Unsupported enum или malformed value.
- Отказ driver.
- Ошибка persistence.
- Повторный выбор активного цвета.
- Запуск без сохранённой настройки.

Обсуждение ASIL

При заданных предположениях невозможность применить декоративный цвет не создаёт safety-relevant вреда, поэтому это упражнение QM. Дисциплина кодирования и тестирования сохраняется, а отсутствие ASIL не означает отсутствие требований к качеству.

ТИПИЧНЫЕ ОШИБКИ НА ИНТЕРВЬЮ

- Начать реализацию до согласования safe state.
- Угадать единицы или включительность порога.
- Называть каждый автомобильный компонент ASIL D.
- Говорить, что unit tests доказывают соответствие ISO 26262.
- Считать line coverage эквивалентом requirements coverage.
- Тестировать только успешное поведение.
- Мокировать приватные методы и порядок реализации.
- Забыть NaN, infinity, stale timestamps и повторные события.
- Использовать sleep в тестах вместо injected clock.
- Добавить dynamic allocation, exceptions или threads, не спросив, разрешены ли они.
- Спрятать предположение в коде вместо его явного объявления.
- Переусложнить дизайн так, что не останется работающего вертикального среза.

ЧЕКЛИСТ САМОПРОВЕРКИ

- Можно ли связать каждую production branch с согласованным требованием?
- Есть ли для каждого требования хотя бы один тест?
- Присутствуют ли позитивные, негативные, граничные случаи и отказы?
- Управляются ли все safety-relevant зависимости через mocks или fakes?
- Явно ли определён safe state?
- Явны ли время и единицы?
- Детерминированы ли повторные вызовы и переходы состояний?
- Проверяются ли запрещённые side effects?
- Считаются ли compiler warnings дефектами?
- Реализация уже спецификации, а не шире неё?
- Могу ли я назвать integration и target tests, которые unit tests не заменяют?
- Могу ли я обсуждать ASIL, не заявляя прямой проектный опыт ISO 26262?

ОФИЦИАЛЬНЫЕ ИСТОЧНИКИ

- Пакет стандартов ISO 26262 и назначение частей 1–10: https://www.iso.org/publication/PUB200262.html
- ISO 26262-3:2018, concept phase, item definition, HARA и functional safety concept: https://www.iso.org/standard/68385.html
- ISO 26262-6:2018, product development at the software level: https://www.iso.org/standard/68388.html
- ISO 26262-9:2018, ASIL-oriented и safety-oriented analyses: https://www.iso.org/standard/68391.html
- ISO 26262-10:2018, guidelines on ISO 26262: https://www.iso.org/standard/68392.html

Дата исследования: 2026-10-27.
