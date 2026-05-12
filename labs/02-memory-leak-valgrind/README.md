# Lab 02 - Memory Leak with Valgrind

## Objective

This lab introduces memory leak detection in C using Valgrind.

The goal is to use Valgrind to:

- run a C program under memory analysis
- detect memory that was allocated but never released
- identify where the allocation happened
- understand why the program appears to work while still being incorrect

This lab is intentionally simple. The focus is to learn how to observe memory ownership problems with a clean and reproducible workflow.

## Bug description

The program simulates loading device readings from an embedded or IoT system.

The function `load_device_readings()` allocates memory dynamically with `malloc()` and returns it to the caller.

The program uses the allocated memory correctly, but never releases it with `free()`.

The program finishes without crashing, but Valgrind reports a memory leak.

## Files

```text
buggy.c   - Program with an intentional memory leak
fixed.c   - Corrected version with proper memory cleanup
Makefile  - Builds both versions
```

## Build

```bash
make
```

This creates two executables:

```text
buggy
fixed
```

## Run the buggy program normally

```bash
./buggy
```

Expected result:

```text
Loading device readings...

Device readings:
- temperature-sensor: 22.50°C, battery 87%
- door-sensor: 19.00°C, battery 64%
- humidity-sensor: 24.10°C, battery 92%

Report completed.
```

The program appears to work correctly.

## Run with Valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./buggy
```

Expected result:

```text
HEAP SUMMARY:
    in use at exit: ... bytes in 1 blocks
  total heap usage: ... allocs, ... frees, ... bytes allocated

... bytes in 1 blocks are definitely lost
```

The exact number of bytes may vary depending on the compiler and platform.

The important part is:

```text
definitely lost
```

## Meaning of the Valgrind report

`definitely lost` means that the program allocated memory, but no valid pointer to that memory remained when the program exited.

In this lab, the allocation happens inside:

```c
DeviceReading *readings = malloc(count * sizeof(DeviceReading));
```

The memory is returned to `main()`, used correctly, but never released.

## Root cause

The caller owns the memory returned by `load_device_readings()`.

Because `main()` receives the allocated pointer, `main()` is responsible for freeing it when the data is no longer needed.

The buggy version forgets this step.

## Run the fixed program with Valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./fixed
```

Expected result:

```text
All heap blocks were freed -- no leaks are possible
```

The fixed version releases the memory with `free(readings)` after the allocated data is no longer needed.

## Clean build files

```bash
make clean
```

## Key lesson

A memory leak does not always crash the program immediately.

In long-running software, such as daemons, embedded services, IoT gateways, or monitoring tools, repeated leaks can slowly consume memory and eventually destabilize the system.

A good debugging workflow is:

1. Run the program normally.
2. Confirm that the visible behavior looks correct.
3. Run the program with Valgrind.
4. Look for `definitely lost`.
5. Find where the leaked memory was allocated.
6. Identify who owns the allocated memory.
7. Add the missing cleanup in the correct place.

