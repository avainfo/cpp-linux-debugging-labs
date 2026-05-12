# Lab 03 - Use-after-free with AddressSanitizer

## Objective

This lab introduces use-after-free detection in C using AddressSanitizer.

The goal is to use AddressSanitizer to:

- detect invalid memory access after `free()`
- identify where the memory was allocated
- identify where the memory was freed
- identify where the invalid access happened
- understand why keeping a pointer after cleanup can be dangerous

This lab is intentionally simple. The focus is to make the bug easy to reproduce, easy to observe, and easy to explain.

## Bug description

The program simulates opening a device session.

The session is allocated dynamically with `malloc()`.

The program then closes the session by calling `free()`.

After that, the buggy version continues to use the same pointer and tries to print data from the freed session.

This is called a use-after-free.

## Files

```text
buggy.c   - Program with an intentional use-after-free bug
Makefile  - Builds the buggy version with AddressSanitizer enabled
```

A fixed version will be added later.

## Build

```bash
make
```

This creates the executable:

```text
buggy
```

The program is compiled with debugging symbols and AddressSanitizer using:

```text
-g -O0 -fsanitize=address -fno-omit-frame-pointer
```

These flags make the AddressSanitizer report easier to understand:

* `-g` adds debug symbols, so the report can show source file names and line numbers
* `-O0` disables compiler optimizations, which keeps the code easier to debug
* `-fsanitize=address` enables AddressSanitizer
* `-fno-omit-frame-pointer` improves the quality of stack traces

## Run the buggy program

```bash
./buggy
```

Expected result:

```text
Opening device session...
Session opened for sensor-gateway-01
Closing device session...
Printing session summary after close...
```

Then AddressSanitizer should report an error similar to:

```text
ERROR: AddressSanitizer: heap-use-after-free
```

The exact output may vary depending on your compiler and system.

## What AddressSanitizer reports

AddressSanitizer usually shows three important locations:

1. Where the invalid memory access happened
2. Where the memory was freed
3. Where the memory was originally allocated

Look for sections similar to:

```text
READ of size ...
freed by thread T0 here:
previously allocated by thread T0 here:
```

This makes AddressSanitizer very useful for debugging memory lifetime errors.

## Root cause

The pointer `session` still contains the address of the allocated memory after `close_device_session(session)`.

However, the memory no longer belongs to the program after `free()`.

The buggy version does this:

```c
close_device_session(session);

print_session_summary(session);
```

At this point, `session` points to freed memory.

The pointer value still exists, but it is no longer valid.

## Clean build files

```bash
make clean
```

## Key lesson

Calling `free()` does not destroy the pointer variable itself.

It releases the memory block that the pointer was pointing to.

After `free()`, the pointer must not be used anymore unless it is assigned a new valid address.

A good debugging workflow is:

1. Compile with AddressSanitizer.
2. Run the program normally.
3. Read the AddressSanitizer report.
4. Find the invalid access location.
5. Find where the memory was freed.
6. Find where the memory was allocated.
7. Fix the ownership and lifetime logic.

