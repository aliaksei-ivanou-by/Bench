FFmpeg, libavfilter, libavformat and libav

1. TECHNOLOGY PROFILE

Category: Media
Relevant scope: FFmpeg libraries in the live and VOD media pipeline; grouped because libavfilter, libavformat and the libav family are components of the same FFmpeg project.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

FFmpeg is a multimedia framework containing command-line tools and libraries for demuxing, decoding, filtering, encoding and muxing. libavformat handles containers and protocols; libavfilter executes filter graphs; timestamps and time bases connect the stages.

3. CORE CONCEPTS AND INTERNAL MODEL

- AVPacket represents compressed data and AVFrame decoded audio or video.
- Each stream and link has a rational time base; PTS and DTS must be rescaled deliberately.
- A filter graph is a directed graph of sources, filters, links and sinks with negotiated formats.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Separate packet and frame ownership, drain codecs and filters on end of stream, normalize timestamps at defined boundaries and instrument both processing and queue time. Validate output timestamps and media, not merely successful API returns.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

FFmpeg offers broad format support and high performance but has a complex stateful API and version-sensitive behavior. GStreamer provides a component pipeline model; platform media frameworks can simplify targeted deployments.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Wrong time-base conversion causes drift and manifest mismatch.
- Excess queues and temporal filters add latency.
- Missing flush and drain steps drop delayed frames at transitions.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

The candidate instrumented libavfilter and queue boundaries, found unnecessary frame accumulation and an avoidable copy/synchronization step, and reduced end-to-end latency by four seconds. Caption data was extracted through FFmpeg frame and format APIs.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does FFmpeg, libavfilter, libavformat and libav solve here?
Answer: FFmpeg is a multimedia framework containing command-line tools and libraries for demuxing, decoding, filtering, encoding and muxing. libavformat handles containers and protocols; libavfilter executes filter graphs; timestamps and time bases connect the stages.

2. Which internal concepts matter most?
Answer: AVPacket represents compressed data and AVFrame decoded audio or video. Each stream and link has a rational time base; PTS and DTS must be rescaled deliberately.

3. What would you make explicit in a production design?
Answer: Separate packet and frame ownership, drain codecs and filters on end of stream, normalize timestamps at defined boundaries and instrument both processing and queue time. Validate output timestamps and media, not merely successful API returns.

4. What is the main tradeoff or alternative?
Answer: FFmpeg offers broad format support and high performance but has a complex stateful API and version-sensitive behavior. GStreamer provides a component pipeline model; platform media frameworks can simplify targeted deployments.

5. Which failure would you test first?
Answer: Wrong time-base conversion causes drift and manifest mismatch. In this project context, the candidate instrumented libavfilter and queue boundaries, found unnecessary frame accumulation and an avoidable copy/synchronization step, and reduced end-to-end latency by four seconds. Caption data was extracted through FFmpeg frame and format APIs.

9. SOURCES

Research date: 2026-10-20.

- https://www.ffmpeg.org/documentation.html
- https://ffmpeg.org/ffmpeg-filters.html
- https://ffmpeg.org/libavfilter.html
