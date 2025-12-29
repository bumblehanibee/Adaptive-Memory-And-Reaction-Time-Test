# Adaptive-Memory-And-Reaction-Time-Test
A C++ system assessment tool measuring reaction time and memory based on cognitive agility.

## Introduction
In a high-speed ICT environment, human 'cognitive lag' can lead to critical errors. This system provides a data-driven way to measure and improve mental processing speeds.

## Features
- **Stroop Effect Module:** Tests cognitive interference using colored text.
- **Sentence Scramble:** Tests logical processing and sentence reconstruction.
- **Word Retype:** Benchmarks short-term memory retention.

## Scoring & Penalties
- **Response Threshold:** 4.0 seconds.
- **Penalty induction:** +5.0 seconds for exceeding the threshold or getting an answer wrong within the 3-time attempts.
- **Precision:** Results are calculated to the millisecond using the `<chrono>` library.

## Requirements
- **OS:** Windows (Required for `<windows.h>`)
- **Compiler:** C++11 or higher.
