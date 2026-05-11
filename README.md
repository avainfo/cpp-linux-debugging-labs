# C/C++ Linux Debugging Labs

Practical debugging exercises for C/C++ developers working on Linux systems.

This repository contains intentionally broken programs used to practice debugging with real Linux tools such as GDB, Valgrind, sanitizers, strace, systemd and journalctl.

It is designed for technical training, junior developer coaching and practical debugging methodology.

## Topics covered

- Segmentation faults
- Invalid memory access
- Use-after-free
- Double free
- Memory leaks
- Race conditions
- Deadlocks
- Core dumps
- GDB
- Valgrind
- AddressSanitizer
- ThreadSanitizer
- strace
- systemd service failures
- journalctl-based investigation

## Why this repository exists

Many developers can write code, but struggle when a program crashes, freezes, leaks memory or behaves inconsistently.

These labs teach a structured debugging approach:

1. Reproduce the issue
2. Observe the symptoms
3. Collect evidence
4. Form hypotheses
5. Use the right tool
6. Validate the root cause
7. Document the fix

The goal is not only to fix bugs, but to learn how to reason from symptoms to evidence.

## Prerequisites

Recommended environment:

- Linux
- GCC or Clang
- Make
- GDB
- Valgrind
- strace
- systemd
- journalctl

Optional but recommended:

- AddressSanitizer
- ThreadSanitizer
- CMake

## Labs

| Lab | Topic | Main tool |
|---|---|---|
| 01 | Segmentation fault | GDB |
| 02 | Memory leak | Valgrind |
| 03 | Use-after-free | AddressSanitizer |
| 04 | Deadlock | GDB |
| 05 | Missing file / syscall error | strace |
| 06 | Crashing Linux service | systemd + journalctl |

## Suggested workflow

For each lab:

1. Build the broken program
2. Run it and observe the failure
3. Reproduce the issue reliably
4. Investigate with the suggested tool
5. Identify the root cause
6. Fix the bug
7. Write a short debugging note

Example debugging note:

```txt
Symptom:
Tool used:
Evidence found:
Root cause:
Fix:
Lesson learned:
```

## Repository structure

```txt
cpp-linux-debugging-labs/
├── labs/
│   ├── 01-segfault-gdb/
│   ├── 02-memory-leak-valgrind/
│   ├── 03-use-after-free-asan/
│   ├── 04-deadlock-gdb/
│   ├── 05-missing-file-strace/
│   └── 06-systemd-service-crash/
├── docs/
│   └── debugging-methodology.md
├── LICENSE
└── README.md
```

## Commercial relevance

This repository supports:

* C/C++ training
* Linux debugging training
* junior developer coaching
* technical rescue preparation
* embedded Linux reliability fundamentals

It demonstrates a practical debugging approach based on reproduction, evidence collection, tool-assisted investigation and clear technical documentation.

## License

This project is released under the MIT License.

The code and exercises are provided for educational purposes and may be reused, modified and adapted with attribution.
