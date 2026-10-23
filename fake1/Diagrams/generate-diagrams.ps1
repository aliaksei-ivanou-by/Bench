$ErrorActionPreference = 'Stop'

$outputDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$utf8NoBom = [System.Text.UTF8Encoding]::new($false)

function ConvertTo-SvgText {
    param([Parameter(Mandatory)][string]$Text)
    return [System.Security.SecurityElement]::Escape($Text)
}

function New-Text {
    param(
        [int]$X,
        [int]$Y,
        [string]$Text,
        [int]$Size = 18,
        [string]$Weight = '400',
        [string]$Color = '#0f172a',
        [string]$Anchor = 'middle'
    )
    $safe = ConvertTo-SvgText $Text
    return "<text x=`"$X`" y=`"$Y`" text-anchor=`"$Anchor`" font-size=`"$Size`" font-weight=`"$Weight`" fill=`"$Color`">$safe</text>"
}

function New-Node {
    param(
        [int]$X,
        [int]$Y,
        [int]$Width,
        [int]$Height,
        [string[]]$Lines,
        [ValidateSet('neutral', 'blue', 'green', 'red', 'amber', 'slate')]
        [string]$Style = 'neutral',
        [int]$FontSize = 16
    )

    $styles = @{
        neutral = @{ Fill = '#ffffff'; Stroke = '#94a3b8'; Text = '#0f172a' }
        blue    = @{ Fill = '#eff6ff'; Stroke = '#3b82f6'; Text = '#1e3a8a' }
        green   = @{ Fill = '#ecfdf5'; Stroke = '#22c55e'; Text = '#14532d' }
        red     = @{ Fill = '#fef2f2'; Stroke = '#ef4444'; Text = '#7f1d1d' }
        amber   = @{ Fill = '#fffbeb'; Stroke = '#f59e0b'; Text = '#78350f' }
        slate   = @{ Fill = '#f1f5f9'; Stroke = '#64748b'; Text = '#334155' }
    }
    $palette = $styles[$Style]
    $builder = [System.Text.StringBuilder]::new()
    [void]$builder.AppendLine("<rect x=`"$X`" y=`"$Y`" width=`"$Width`" height=`"$Height`" rx=`"12`" fill=`"$($palette.Fill)`" stroke=`"$($palette.Stroke)`" stroke-width=`"2.5`"/>")
    $lineHeight = [int][Math]::Round($FontSize * 1.3)
    $firstY = [int][Math]::Round($Y + ($Height / 2) - (($Lines.Count - 1) * $lineHeight / 2) + ($FontSize * 0.35))
    for ($index = 0; $index -lt $Lines.Count; $index++) {
        $safe = ConvertTo-SvgText $Lines[$index]
        $textY = $firstY + ($index * $lineHeight)
        [void]$builder.AppendLine("<text x=`"$($X + ($Width / 2))`" y=`"$textY`" text-anchor=`"middle`" font-size=`"$FontSize`" font-weight=`"600`" fill=`"$($palette.Text)`">$safe</text>")
    }
    return $builder.ToString().TrimEnd()
}

function New-Arrow {
    param(
        [int]$X1,
        [int]$Y1,
        [int]$X2,
        [int]$Y2,
        [ValidateSet('normal', 'green', 'red', 'blue')]
        [string]$Style = 'normal',
        [switch]$Dashed
    )
    $colors = @{ normal = '#64748b'; green = '#16a34a'; red = '#dc2626'; blue = '#2563eb' }
    $dash = if ($Dashed) { ' stroke-dasharray="9 7"' } else { '' }
    return "<line x1=`"$X1`" y1=`"$Y1`" x2=`"$X2`" y2=`"$Y2`" stroke=`"$($colors[$Style])`" stroke-width=`"3`" fill=`"none`" marker-end=`"url(#arrow-$Style)`"$dash/>"
}

function New-PathArrow {
    param(
        [string]$Path,
        [ValidateSet('normal', 'green', 'red', 'blue')]
        [string]$Style = 'normal',
        [switch]$Dashed
    )
    $colors = @{ normal = '#64748b'; green = '#16a34a'; red = '#dc2626'; blue = '#2563eb' }
    $dash = if ($Dashed) { ' stroke-dasharray="9 7"' } else { '' }
    return "<path d=`"$Path`" stroke=`"$($colors[$Style])`" stroke-width=`"3`" fill=`"none`" marker-end=`"url(#arrow-$Style)`"$dash/>"
}

function New-Panel {
    param([int]$X, [string]$Title, [ValidateSet('before', 'after')][string]$Kind)
    $fill = if ($Kind -eq 'before') { '#fff7f7' } else { '#f4fbf7' }
    $stroke = if ($Kind -eq 'before') { '#fecaca' } else { '#bbf7d0' }
    $badgeFill = if ($Kind -eq 'before') { '#fee2e2' } else { '#dcfce7' }
    $badgeText = if ($Kind -eq 'before') { '#991b1b' } else { '#166534' }
    $safe = ConvertTo-SvgText $Title
    return @"
<rect x="$X" y="112" width="730" height="748" rx="22" fill="$fill" stroke="$stroke" stroke-width="3"/>
<rect x="$($X + 28)" y="136" width="158" height="42" rx="21" fill="$badgeFill"/>
<text x="$($X + 107)" y="164" text-anchor="middle" font-size="18" font-weight="700" fill="$badgeText">$safe</text>
"@.TrimEnd()
}

function New-SvgDocument {
    param([string]$Title, [string]$Subtitle, [string]$Body, [string]$Footer)
    $safeTitle = ConvertTo-SvgText $Title
    $safeSubtitle = ConvertTo-SvgText $Subtitle
    $safeFooter = ConvertTo-SvgText $Footer
    return @"
<svg xmlns="http://www.w3.org/2000/svg" width="1600" height="1000" viewBox="0 0 1600 1000" role="img" aria-labelledby="title desc" font-family="Segoe UI, Arial, sans-serif">
  <title id="title">$safeTitle</title>
  <desc id="desc">$safeSubtitle</desc>
  <defs>
    <filter id="shadow" x="-20%" y="-20%" width="140%" height="140%"><feDropShadow dx="0" dy="5" stdDeviation="7" flood-color="#0f172a" flood-opacity="0.08"/></filter>
    <marker id="arrow-normal" markerWidth="11" markerHeight="8" refX="10" refY="4" orient="auto"><polygon points="0 0,11 4,0 8" fill="#64748b"/></marker>
    <marker id="arrow-green" markerWidth="11" markerHeight="8" refX="10" refY="4" orient="auto"><polygon points="0 0,11 4,0 8" fill="#16a34a"/></marker>
    <marker id="arrow-red" markerWidth="11" markerHeight="8" refX="10" refY="4" orient="auto"><polygon points="0 0,11 4,0 8" fill="#dc2626"/></marker>
    <marker id="arrow-blue" markerWidth="11" markerHeight="8" refX="10" refY="4" orient="auto"><polygon points="0 0,11 4,0 8" fill="#2563eb"/></marker>
  </defs>
  <rect width="1600" height="1000" fill="#f8fafc"/>
  <text x="800" y="48" text-anchor="middle" font-size="31" font-weight="700" fill="#0f172a">$safeTitle</text>
  <text x="800" y="79" text-anchor="middle" font-size="17" fill="#475569">$safeSubtitle</text>
$Body
  <rect x="40" y="895" width="1520" height="66" rx="18" fill="#0f172a" filter="url(#shadow)"/>
  <text x="800" y="936" text-anchor="middle" font-size="20" font-weight="650" fill="#ffffff">$safeFooter</text>
</svg>
"@
}

function New-ProtocolDiagram {
    param([ValidateSet('en', 'ru')][string]$Language)
    if ($Language -eq 'ru') {
        $l = @{
            Title = 'Миграция управления: JSON-RPC → gRPC и Protobuf'
            Subtitle = 'Явный контракт, безопасная совместимость версий и поэтапный переход'
            Before = 'ДО'; After = 'ПОСЛЕ'
            Orchestrator = @('Оркестратор'); Json = @('JSON-RPC', 'текст'); Control = @('Сервис', 'управления'); Encoder = @('Кодировщик /', 'выходной сервис')
            Problem = @('Неявная схема', 'Расхождения только в runtime', 'Ручное версионирование')
            Proto = @('Общий .proto-контракт'); Generated = @('Сгенерированные интерфейсы', 'C++ · Java · Kotlin')
            Caller = @('Модель', 'вызывающего'); Adapter = @('Адаптер'); Client = @('gRPC', 'клиент'); Server = @('gRPC', 'сервер'); Callee = @('Модель', 'сервиса')
            Parallel = @('JSON-RPC + gRPC'); Shadow = @('Теневое', 'сравнение'); Canary = @('Канареечный', 'переход'); Only = @('Только gRPC')
            Contract = 'типы · ошибки · дедлайны · версионирование'
            Flow = 'сборка → сравнение → канареечный переход → отключение fallback'
            Footer = 'Результат: затраты на сериализацию ≈ −40% · размер запроса ≈ −60% · несовместимости выявляются до выпуска'
        }
    } else {
        $l = @{
            Title = 'Control-plane migration: JSON-RPC → gRPC and Protobuf'
            Subtitle = 'Explicit contracts, mixed-version safety and a staged cutover'
            Before = 'BEFORE'; After = 'AFTER'
            Orchestrator = @('Orchestrator'); Json = @('JSON-RPC', 'text'); Control = @('Control', 'service'); Encoder = @('Encoder /', 'output service')
            Problem = @('Implicit schema', 'Runtime-only mismatches', 'Informal versioning')
            Proto = @('Shared .proto contract'); Generated = @('Generated interfaces', 'C++ · Java · Kotlin')
            Caller = @('Caller', 'model'); Adapter = @('Adapter'); Client = @('gRPC', 'client'); Server = @('gRPC', 'server'); Callee = @('Callee', 'model')
            Parallel = @('JSON-RPC + gRPC'); Shadow = @('Shadow', 'comparison'); Canary = @('Canary', 'cutover'); Only = @('gRPC only')
            Contract = 'typed fields · errors · deadlines · versioning'
            Flow = 'build → compare → canary → remove fallback'
            Footer = 'Result: serialization overhead ≈ −40% · request size ≈ −60% · incompatibilities caught before production'
        }
    }

    $b = [System.Text.StringBuilder]::new()
    [void]$b.AppendLine((New-Panel -X 40 -Title $l.Before -Kind before))
    [void]$b.AppendLine((New-Panel -X 830 -Title $l.After -Kind after))

    [void]$b.AppendLine((New-Node -X 105 -Y 205 -Width 240 -Height 66 -Lines $l.Orchestrator -Style slate))
    [void]$b.AppendLine((New-Arrow -X1 225 -Y1 271 -X2 225 -Y2 315))
    [void]$b.AppendLine((New-Node -X 105 -Y 325 -Width 240 -Height 66 -Lines $l.Json -Style amber))
    [void]$b.AppendLine((New-Arrow -X1 225 -Y1 391 -X2 225 -Y2 435))
    [void]$b.AppendLine((New-Node -X 105 -Y 445 -Width 240 -Height 66 -Lines $l.Control -Style neutral))
    [void]$b.AppendLine((New-Arrow -X1 225 -Y1 511 -X2 225 -Y2 555))
    [void]$b.AppendLine((New-Node -X 105 -Y 565 -Width 240 -Height 66 -Lines $l.Json -Style amber))
    [void]$b.AppendLine((New-Arrow -X1 225 -Y1 631 -X2 225 -Y2 675))
    [void]$b.AppendLine((New-Node -X 105 -Y 685 -Width 240 -Height 76 -Lines $l.Encoder -Style neutral))
    [void]$b.AppendLine((New-Node -X 405 -Y 337 -Width 300 -Height 190 -Lines $l.Problem -Style red -FontSize 17))
    [void]$b.AppendLine((New-PathArrow -Path 'M345 358 H377 V432 H405' -Style red -Dashed))
    [void]$b.AppendLine((New-PathArrow -Path 'M345 598 H377 V432 H405' -Style red -Dashed))

    [void]$b.AppendLine((New-Node -X 1015 -Y 190 -Width 330 -Height 64 -Lines $l.Proto -Style blue -FontSize 18))
    [void]$b.AppendLine((New-Arrow -X1 1180 -Y1 254 -X2 1180 -Y2 292 -Style blue))
    [void]$b.AppendLine((New-Node -X 990 -Y 302 -Width 380 -Height 72 -Lines $l.Generated -Style blue))
    [void]$b.AppendLine((New-Text -X 1180 -Y 396 -Text $l.Contract -Size 16 -Weight 600 -Color '#1d4ed8'))

    $nodes = @(
        @{ X = 850; Lines = $l.Caller; Style = 'neutral' },
        @{ X = 990; Lines = $l.Adapter; Style = 'slate' },
        @{ X = 1120; Lines = $l.Client; Style = 'blue' },
        @{ X = 1250; Lines = $l.Server; Style = 'blue' },
        @{ X = 1380; Lines = $l.Callee; Style = 'neutral' }
    )
    foreach ($node in $nodes) {
        [void]$b.AppendLine((New-Node -X $node.X -Y 430 -Width 110 -Height 74 -Lines $node.Lines -Style $node.Style -FontSize 14))
    }
    foreach ($x in @(960, 1100, 1230, 1360)) {
        [void]$b.AppendLine((New-Arrow -X1 $x -Y1 467 -X2 ($x + 28) -Y2 467 -Style blue))
    }
    [void]$b.AppendLine((New-PathArrow -Path 'M1070 374 V414 H905 V430' -Style blue -Dashed))
    [void]$b.AppendLine((New-PathArrow -Path 'M1290 374 V414 H1435 V430' -Style blue -Dashed))

    $migration = @(
        @{ X = 855; Lines = $l.Parallel; Style = 'amber'; W = 160 },
        @{ X = 1050; Lines = $l.Shadow; Style = 'blue'; W = 140 },
        @{ X = 1225; Lines = $l.Canary; Style = 'blue'; W = 140 },
        @{ X = 1400; Lines = $l.Only; Style = 'green'; W = 125 }
    )
    foreach ($node in $migration) {
        [void]$b.AppendLine((New-Node -X $node.X -Y 650 -Width $node.W -Height 74 -Lines $node.Lines -Style $node.Style -FontSize 14))
    }
    [void]$b.AppendLine((New-Arrow -X1 1015 -Y1 687 -X2 1048 -Y2 687 -Style green))
    [void]$b.AppendLine((New-Arrow -X1 1190 -Y1 687 -X2 1223 -Y2 687 -Style green))
    [void]$b.AppendLine((New-Arrow -X1 1365 -Y1 687 -X2 1398 -Y2 687 -Style green))
    [void]$b.AppendLine((New-Text -X 1180 -Y 775 -Text $l.Flow -Size 16 -Weight 600 -Color '#166534'))

    return New-SvgDocument -Title $l.Title -Subtitle $l.Subtitle -Body $b.ToString() -Footer $l.Footer
}

function New-UploadDiagram {
    param([ValidateSet('en', 'ru')][string]$Language)
    if ($Language -eq 'ru') {
        $l = @{
            Title = 'Надёжная доставка сегментов в облачные хранилища'
            Subtitle = 'Управляемая перегрузка, подтверждение объекта до публикации и восстановление после сбоев'
            Before = 'ДО'; After = 'ПОСЛЕ'
            Encoded = @('Закодированные', 'сегменты'); Queue = @('Одна общая', 'очередь'); Policy = @('Одинаковые', 'параллелизм и retry'); Providers = @('Все облачные', 'провайдеры')
            Risks = @('Рост очереди', 'Throttling', 'Разные дедлайны')
            ManifestRisk = @('Манифест мог ждать слишком долго', 'или ссылаться на неподтверждённый объект')
            QueueA = @('Ограниченная', 'очередь A'); QueueB = @('Ограниченная', 'очередь B'); QueueC = @('Ограниченная', 'очередь C')
            Controller = @('Адаптивный контроллер', 'лимиты · latency · throttling'); Adapter = @('Адаптер провайдера', 'ошибки · retry budget', 'идемпотентность')
            Confirmed = @('Объект загружен', 'и подтверждён'); Barrier = @('Барьер публикации'); Manifest = @('Манифест')
            Outage = @('Сбой'); Retention = @('Локальное хранение', 'порядок сохранён'); Recovery = @('Упорядоченное', 'восстановление')
            Footer = 'Результат: upload SLA 90% → 99.9% · память ограничена · объект подтверждён до публикации манифеста'
        }
    } else {
        $l = @{
            Title = 'Reliable segment delivery to cloud storage'
            Subtitle = 'Controlled overload, object-before-manifest publication and deterministic recovery'
            Before = 'BEFORE'; After = 'AFTER'
            Encoded = @('Encoded', 'segments'); Queue = @('One shared', 'queue'); Policy = @('One concurrency', 'and retry policy'); Providers = @('All cloud', 'providers')
            Risks = @('Queue growth', 'Throttling', 'Different deadlines')
            ManifestRisk = @('Manifest could wait too long', 'or reference an unconfirmed object')
            QueueA = @('Bounded', 'queue A'); QueueB = @('Bounded', 'queue B'); QueueC = @('Bounded', 'queue C')
            Controller = @('Adaptive controller', 'limits · latency · throttling'); Adapter = @('Provider adapter', 'error class · retry budget', 'idempotency')
            Confirmed = @('Object uploaded', 'and confirmed'); Barrier = @('Publication barrier'); Manifest = @('Manifest')
            Outage = @('Outage'); Retention = @('Local retention', 'ordering preserved'); Recovery = @('Ordered', 'recovery')
            Footer = 'Result: upload SLA improved from 90% to 99.9% · bounded memory · object-before-manifest guaranteed'
        }
    }

    $b = [System.Text.StringBuilder]::new()
    [void]$b.AppendLine((New-Panel -X 40 -Title $l.Before -Kind before))
    [void]$b.AppendLine((New-Panel -X 830 -Title $l.After -Kind after))

    [void]$b.AppendLine((New-Node -X 95 -Y 235 -Width 150 -Height 76 -Lines $l.Encoded -Style neutral))
    [void]$b.AppendLine((New-Arrow -X1 245 -Y1 273 -X2 285 -Y2 273))
    [void]$b.AppendLine((New-Node -X 295 -Y 235 -Width 150 -Height 76 -Lines $l.Queue -Style amber))
    [void]$b.AppendLine((New-Arrow -X1 445 -Y1 273 -X2 485 -Y2 273))
    [void]$b.AppendLine((New-Node -X 495 -Y 225 -Width 190 -Height 96 -Lines $l.Policy -Style amber -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 590 -Y1 321 -X2 590 -Y2 365))
    [void]$b.AppendLine((New-Node -X 495 -Y 375 -Width 190 -Height 82 -Lines $l.Providers -Style neutral))
    [void]$b.AppendLine((New-Node -X 245 -Y 505 -Width 310 -Height 150 -Lines $l.Risks -Style red -FontSize 18))
    [void]$b.AppendLine((New-PathArrow -Path 'M370 311 V475 H400 V505' -Style red -Dashed))
    [void]$b.AppendLine((New-Node -X 140 -Y 700 -Width 520 -Height 82 -Lines $l.ManifestRisk -Style red -FontSize 16))
    [void]$b.AppendLine((New-PathArrow -Path 'M590 457 V675 H530 V700' -Style red -Dashed))

    [void]$b.AppendLine((New-Node -X 860 -Y 205 -Width 150 -Height 72 -Lines $l.Encoded -Style neutral))
    [void]$b.AppendLine((New-PathArrow -Path 'M1010 241 H1040 V195 H1065' -Style blue))
    [void]$b.AppendLine((New-PathArrow -Path 'M1010 241 H1065' -Style blue))
    [void]$b.AppendLine((New-PathArrow -Path 'M1010 241 H1040 V287 H1065' -Style blue))
    [void]$b.AppendLine((New-Node -X 1075 -Y 160 -Width 150 -Height 70 -Lines $l.QueueA -Style blue -FontSize 14))
    [void]$b.AppendLine((New-Node -X 1075 -Y 245 -Width 150 -Height 70 -Lines $l.QueueB -Style blue -FontSize 14))
    [void]$b.AppendLine((New-Node -X 1075 -Y 330 -Width 150 -Height 70 -Lines $l.QueueC -Style blue -FontSize 14))
    [void]$b.AppendLine((New-PathArrow -Path 'M1225 195 H1260 V280 H1290' -Style green))
    [void]$b.AppendLine((New-Arrow -X1 1225 -Y1 280 -X2 1290 -Y2 280 -Style green))
    [void]$b.AppendLine((New-PathArrow -Path 'M1225 365 H1260 V280 H1290' -Style green))
    [void]$b.AppendLine((New-Node -X 1300 -Y 230 -Width 230 -Height 100 -Lines $l.Controller -Style green -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1415 -Y1 330 -X2 1415 -Y2 372 -Style green))
    [void]$b.AppendLine((New-Node -X 1290 -Y 382 -Width 250 -Height 100 -Lines $l.Adapter -Style blue -FontSize 13))
    [void]$b.AppendLine((New-Arrow -X1 1415 -Y1 482 -X2 1415 -Y2 520 -Style green))
    [void]$b.AppendLine((New-Node -X 1300 -Y 530 -Width 230 -Height 76 -Lines $l.Confirmed -Style green -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1415 -Y1 606 -X2 1415 -Y2 644 -Style green))
    [void]$b.AppendLine((New-Node -X 1300 -Y 654 -Width 230 -Height 72 -Lines $l.Barrier -Style green -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1415 -Y1 726 -X2 1415 -Y2 764 -Style green))
    [void]$b.AppendLine((New-Node -X 1320 -Y 774 -Width 190 -Height 62 -Lines $l.Manifest -Style green))

    [void]$b.AppendLine((New-Node -X 855 -Y 545 -Width 110 -Height 64 -Lines $l.Outage -Style red -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 965 -Y1 577 -X2 993 -Y2 577 -Style red))
    [void]$b.AppendLine((New-Node -X 1005 -Y 530 -Width 180 -Height 94 -Lines $l.Retention -Style amber -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 1095 -Y1 624 -X2 1095 -Y2 660 -Style green))
    [void]$b.AppendLine((New-Node -X 1005 -Y 670 -Width 180 -Height 80 -Lines $l.Recovery -Style green -FontSize 14))
    [void]$b.AppendLine((New-PathArrow -Path 'M1185 710 H1245 V570 H1300' -Style green))

    return New-SvgDocument -Title $l.Title -Subtitle $l.Subtitle -Body $b.ToString() -Footer $l.Footer
}

function New-LatencyDiagram {
    param([ValidateSet('en', 'ru')][string]$Language)
    if ($Language -eq 'ru') {
        $l = @{
            Title = 'Диагностика и сокращение задержки FFmpeg-конвейера'
            Subtitle = 'От одной непрозрачной метрики к измеримому бюджету каждой стадии'
            Before = 'ДО'; After = 'ПОСЛЕ'
            Input = @('Вход'); Graph = @('FFmpeg graph', 'непрозрачный блок'); Encoder = @('Кодировщик'); Output = @('Выход')
            Timer = @('Один end-to-end таймер'); Profiler = @('CPU-профайлер'); Blind = @('Ожидание в очередях', 'оставалось невидимым')
            Ingest = @('Ingest'); Filters = @('Фильтры'); Queue = @('Очередь'); Encode = @('Encode'); Package = @('Package'); Out = @('Output')
            Telemetry = @('Гистограммы стадий + sampled traces', 'monotonic clock · normalized PTS · low-cardinality labels')
            Dashboard = @('Dashboard', 'latency · queue', 'depth · throughput')
            Finding = @('Лишнее ожидание', 'в очереди'); Copy = @('Лишние copy', 'и sync'); Change = @('Безопасный лимит', '+ изменение graph')
            Flow = 'измерить → локализовать → изменить одну границу → регресс-тест'
            Footer = 'Результат: сквозная задержка −4 секунды · корректность и A/V-синхронизация сохранены'
        }
    } else {
        $l = @{
            Title = 'Diagnosing and reducing FFmpeg pipeline latency'
            Subtitle = 'From one opaque number to a measurable budget for every stage'
            Before = 'BEFORE'; After = 'AFTER'
            Input = @('Input'); Graph = @('FFmpeg graph', 'opaque block'); Encoder = @('Encoder'); Output = @('Output')
            Timer = @('One end-to-end timer'); Profiler = @('CPU profiler'); Blind = @('Queue residence time', 'remained invisible')
            Ingest = @('Ingest'); Filters = @('Filters'); Queue = @('Queue'); Encode = @('Encode'); Package = @('Package'); Out = @('Output')
            Telemetry = @('Stage histograms + sampled traces', 'monotonic clock · normalized PTS · low-cardinality labels')
            Dashboard = @('Dashboard', 'latency · queue', 'depth · throughput')
            Finding = @('Excess queue', 'residence'); Copy = @('Redundant copy', 'and sync'); Change = @('Safe queue limit', '+ graph change')
            Flow = 'measure → isolate → change one boundary → regress'
            Footer = 'Result: end-to-end latency −4 seconds · output correctness and A/V synchronization preserved'
        }
    }

    $b = [System.Text.StringBuilder]::new()
    [void]$b.AppendLine((New-Panel -X 40 -Title $l.Before -Kind before))
    [void]$b.AppendLine((New-Panel -X 830 -Title $l.After -Kind after))

    [void]$b.AppendLine((New-Node -X 75 -Y 260 -Width 110 -Height 68 -Lines $l.Input -Style neutral))
    [void]$b.AppendLine((New-Arrow -X1 185 -Y1 294 -X2 225 -Y2 294))
    [void]$b.AppendLine((New-Node -X 235 -Y 235 -Width 230 -Height 118 -Lines $l.Graph -Style amber -FontSize 18))
    [void]$b.AppendLine((New-Arrow -X1 465 -Y1 294 -X2 505 -Y2 294))
    [void]$b.AppendLine((New-Node -X 515 -Y 260 -Width 125 -Height 68 -Lines $l.Encoder -Style neutral -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 640 -Y1 294 -X2 674 -Y2 294))
    [void]$b.AppendLine((New-Node -X 682 -Y 260 -Width 70 -Height 68 -Lines $l.Output -Style neutral -FontSize 14))
    [void]$b.AppendLine((New-Node -X 195 -Y 445 -Width 310 -Height 76 -Lines $l.Timer -Style amber))
    [void]$b.AppendLine((New-PathArrow -Path 'M130 328 V410 H350 V445' -Style red -Dashed))
    [void]$b.AppendLine((New-PathArrow -Path 'M717 328 V410 H350 V445' -Style red -Dashed))
    [void]$b.AppendLine((New-Node -X 95 -Y 625 -Width 220 -Height 72 -Lines $l.Profiler -Style slate))
    [void]$b.AppendLine((New-Arrow -X1 315 -Y1 661 -X2 355 -Y2 661 -Style red))
    [void]$b.AppendLine((New-Node -X 365 -Y 605 -Width 330 -Height 112 -Lines $l.Blind -Style red -FontSize 18))

    $pipeline = @(
        @{ X = 850; Lines = $l.Ingest }, @{ X = 962; Lines = $l.Filters }, @{ X = 1074; Lines = $l.Queue },
        @{ X = 1186; Lines = $l.Encode }, @{ X = 1298; Lines = $l.Package }, @{ X = 1410; Lines = $l.Out }
    )
    foreach ($node in $pipeline) {
        [void]$b.AppendLine((New-Node -X $node.X -Y 225 -Width 92 -Height 70 -Lines $node.Lines -Style blue -FontSize 14))
    }
    foreach ($x in @(942,1054,1166,1278,1390)) {
        [void]$b.AppendLine((New-Arrow -X1 $x -Y1 260 -X2 ($x + 18) -Y2 260 -Style blue))
    }
    foreach ($x in @(896,1008,1120,1232,1344,1456)) {
        [void]$b.AppendLine((New-Arrow -X1 $x -Y1 295 -X2 $x -Y2 365 -Style blue -Dashed))
    }
    [void]$b.AppendLine((New-Node -X 930 -Y 375 -Width 475 -Height 92 -Lines $l.Telemetry -Style blue -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1405 -Y1 421 -X2 1432 -Y2 421 -Style green))
    [void]$b.AppendLine((New-Node -X 1430 -Y 375 -Width 115 -Height 92 -Lines $l.Dashboard -Style green -FontSize 11))

    [void]$b.AppendLine((New-Node -X 875 -Y 625 -Width 180 -Height 82 -Lines $l.Finding -Style red -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1055 -Y1 666 -X2 1090 -Y2 666 -Style red))
    [void]$b.AppendLine((New-Node -X 1100 -Y 625 -Width 180 -Height 82 -Lines $l.Copy -Style amber -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1280 -Y1 666 -X2 1315 -Y2 666 -Style green))
    [void]$b.AppendLine((New-Node -X 1325 -Y 615 -Width 210 -Height 102 -Lines $l.Change -Style green -FontSize 15))
    [void]$b.AppendLine((New-Text -X 1200 -Y 780 -Text $l.Flow -Size 17 -Weight 650 -Color '#166534'))

    return New-SvgDocument -Title $l.Title -Subtitle $l.Subtitle -Body $b.ToString() -Footer $l.Footer
}

function New-WorkerDiagram {
    param([ValidateSet('en', 'ru')][string]$Language)
    if ($Language -eq 'ru') {
        $l = @{
            Title = 'Синхронизация воркеров кодирования'
            Subtitle = 'Временное владение, fencing token, идемпотентные команды и отдельный барьер публикации'
            Before = 'ДО'; After = 'ПОСЛЕ'
            Delivery = @('RabbitMQ', 'delivery'); Redelivery = @('RabbitMQ', 'redelivery'); WorkerA = @('Worker A', 'считает себя owner'); WorkerB = @('Worker B', 'считает себя owner'); Race = @('Гонка состояния', 'и манифеста')
            Queue = @('RabbitMQ'); Pool = @('Конкурирующие', 'воркеры'); Lease = @('Atomic MySQL lease', '+ generation'); Owner = @('Один активный', 'owner')
            Orchestrator = @('Оркестратор'); Command = @('gRPC-команда', 'command ID · state version · generation · deadline')
            Heartbeat = @('Heartbeat', 'остановился'); Expiry = @('Lease истёк', 'generation + 1'); NewOwner = @('Новый owner')
            Stale = @('Старый worker', 'state / object'); Fence = @('Проверка', 'generation'); Rejected = @('Отклонено', 'как stale')
            Ready = @('SegmentReady', 'index · PTS · generation'); Barrier = @('Manifest barrier'); Publish = @('Публикация')
            Footer = 'Результат: один активный владелец · устаревшие результаты блокируются · переключение без двойной публикации'
        }
    } else {
        $l = @{
            Title = 'Synchronizing encoder workers'
            Subtitle = 'Leases, fencing tokens, idempotent commands and a separate publication barrier'
            Before = 'BEFORE'; After = 'AFTER'
            Delivery = @('RabbitMQ', 'delivery'); Redelivery = @('RabbitMQ', 'redelivery'); WorkerA = @('Worker A', 'believes it owns job'); WorkerB = @('Worker B', 'believes it owns job'); Race = @('State and', 'manifest race')
            Queue = @('RabbitMQ'); Pool = @('Competing', 'workers'); Lease = @('Atomic MySQL lease', '+ generation'); Owner = @('One active', 'owner')
            Orchestrator = @('Orchestrator'); Command = @('gRPC command', 'command ID · state version · generation · deadline')
            Heartbeat = @('Heartbeat', 'stops'); Expiry = @('Lease expires', 'generation + 1'); NewOwner = @('New owner')
            Stale = @('Old worker', 'state / object'); Fence = @('Generation', 'check'); Rejected = @('Rejected', 'as stale')
            Ready = @('SegmentReady', 'index · PTS · generation'); Barrier = @('Manifest barrier'); Publish = @('Publish')
            Footer = 'Result: one active owner · stale output is fenced · failover cannot create duplicate publication'
        }
    }

    $b = [System.Text.StringBuilder]::new()
    [void]$b.AppendLine((New-Panel -X 40 -Title $l.Before -Kind before))
    [void]$b.AppendLine((New-Panel -X 830 -Title $l.After -Kind after))

    [void]$b.AppendLine((New-Node -X 85 -Y 235 -Width 160 -Height 72 -Lines $l.Delivery -Style amber -FontSize 15))
    [void]$b.AppendLine((New-Node -X 85 -Y 435 -Width 160 -Height 72 -Lines $l.Redelivery -Style amber -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 245 -Y1 271 -X2 325 -Y2 271 -Style red))
    [void]$b.AppendLine((New-Arrow -X1 245 -Y1 471 -X2 325 -Y2 471 -Style red))
    [void]$b.AppendLine((New-Node -X 335 -Y 225 -Width 220 -Height 92 -Lines $l.WorkerA -Style red -FontSize 16))
    [void]$b.AppendLine((New-Node -X 335 -Y 425 -Width 220 -Height 92 -Lines $l.WorkerB -Style red -FontSize 16))
    [void]$b.AppendLine((New-PathArrow -Path 'M555 271 H610 V605 H500' -Style red))
    [void]$b.AppendLine((New-PathArrow -Path 'M555 471 H610 V605 H500' -Style red))
    [void]$b.AppendLine((New-Node -X 260 -Y 615 -Width 360 -Height 110 -Lines $l.Race -Style red -FontSize 20))

    [void]$b.AppendLine((New-Node -X 850 -Y 205 -Width 135 -Height 66 -Lines $l.Queue -Style amber -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 985 -Y1 238 -X2 1015 -Y2 238 -Style blue))
    [void]$b.AppendLine((New-Node -X 1025 -Y 195 -Width 160 -Height 86 -Lines $l.Pool -Style blue -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 1185 -Y1 238 -X2 1215 -Y2 238 -Style green))
    [void]$b.AppendLine((New-Node -X 1225 -Y 190 -Width 200 -Height 96 -Lines $l.Lease -Style green -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1425 -Y1 238 -X2 1452 -Y2 238 -Style green))
    [void]$b.AppendLine((New-Node -X 1460 -Y 195 -Width 105 -Height 86 -Lines $l.Owner -Style green -FontSize 13))

    [void]$b.AppendLine((New-Node -X 850 -Y 345 -Width 145 -Height 66 -Lines $l.Orchestrator -Style slate -FontSize 15))
    [void]$b.AppendLine((New-Node -X 1030 -Y 330 -Width 390 -Height 96 -Lines $l.Command -Style blue -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 995 -Y1 378 -X2 1028 -Y2 378 -Style blue))
    [void]$b.AppendLine((New-PathArrow -Path 'M1420 378 H1512 V281' -Style blue))

    [void]$b.AppendLine((New-Node -X 850 -Y 500 -Width 140 -Height 76 -Lines $l.Heartbeat -Style red -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 990 -Y1 538 -X2 1020 -Y2 538 -Style red))
    [void]$b.AppendLine((New-Node -X 1030 -Y 490 -Width 210 -Height 96 -Lines $l.Expiry -Style amber -FontSize 15))
    [void]$b.AppendLine((New-Arrow -X1 1240 -Y1 538 -X2 1270 -Y2 538 -Style green))
    [void]$b.AppendLine((New-Node -X 1280 -Y 500 -Width 180 -Height 76 -Lines $l.NewOwner -Style green -FontSize 15))

    [void]$b.AppendLine((New-Node -X 850 -Y 635 -Width 165 -Height 82 -Lines $l.Stale -Style red -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 1015 -Y1 676 -X2 1045 -Y2 676 -Style red))
    [void]$b.AppendLine((New-Node -X 1055 -Y 635 -Width 170 -Height 82 -Lines $l.Fence -Style amber -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 1225 -Y1 676 -X2 1255 -Y2 676 -Style red))
    [void]$b.AppendLine((New-Node -X 1265 -Y 635 -Width 175 -Height 82 -Lines $l.Rejected -Style red -FontSize 14))

    [void]$b.AppendLine((New-Node -X 850 -Y 765 -Width 220 -Height 74 -Lines $l.Ready -Style blue -FontSize 13))
    [void]$b.AppendLine((New-Arrow -X1 1070 -Y1 802 -X2 1100 -Y2 802 -Style green))
    [void]$b.AppendLine((New-Node -X 1110 -Y 765 -Width 190 -Height 74 -Lines $l.Barrier -Style green -FontSize 14))
    [void]$b.AppendLine((New-Arrow -X1 1300 -Y1 802 -X2 1330 -Y2 802 -Style green))
    [void]$b.AppendLine((New-Node -X 1340 -Y 765 -Width 150 -Height 74 -Lines $l.Publish -Style green -FontSize 15))

    return New-SvgDocument -Title $l.Title -Subtitle $l.Subtitle -Body $b.ToString() -Footer $l.Footer
}

$diagrams = @(
    @{ Name = '01-json-rpc-to-grpc'; Builder = ${function:New-ProtocolDiagram} },
    @{ Name = '02-cloud-upload-reliability'; Builder = ${function:New-UploadDiagram} },
    @{ Name = '03-ffmpeg-latency'; Builder = ${function:New-LatencyDiagram} },
    @{ Name = '04-worker-synchronization'; Builder = ${function:New-WorkerDiagram} }
)

foreach ($diagram in $diagrams) {
    foreach ($language in @('en', 'ru')) {
        $svg = & $diagram.Builder -Language $language
        $svgPath = Join-Path $outputDirectory "$($diagram.Name)-$language.svg"
        $normalizedSvg = ($svg.TrimEnd() -replace "`r?`n", "`r`n") + "`r`n"
        [System.IO.File]::WriteAllText($svgPath, $normalizedSvg, $utf8NoBom)
    }
}

$chromePath = 'C:\Program Files\Google\Chrome\Application\chrome.exe'
if (Test-Path -LiteralPath $chromePath) {
    Get-ChildItem -LiteralPath $outputDirectory -Filter '*.svg' | ForEach-Object {
        $pngPath = [System.IO.Path]::ChangeExtension($_.FullName, '.png')
        $uri = [System.Uri]::new($_.FullName).AbsoluteUri
        & $chromePath --headless=new --disable-gpu --hide-scrollbars --force-device-scale-factor=1 --window-size=1600,1000 "--screenshot=$pngPath" $uri 2>$null | Out-Null
        if (-not (Test-Path -LiteralPath $pngPath)) {
            throw "PNG export failed: $pngPath"
        }
    }
} else {
    Write-Warning 'Google Chrome was not found; SVG files were generated, but PNG export was skipped.'
}

Get-ChildItem -LiteralPath $outputDirectory -File | Sort-Object Name | Select-Object Name, Length
