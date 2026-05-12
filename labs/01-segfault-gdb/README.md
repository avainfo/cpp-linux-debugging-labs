# Lab 01 - Segmentation Fault with GDB

## Objective

This lab introduces a classic C debugging scenario: a segmentation fault caused by dereferencing a `NULL` pointer.

The goal is to use GDB to:

- reproduce the crash
- inspect where the program fails
- read the backtrace
- understand why the pointer is invalid
- compare the buggy version with the fixed version

This lab is intentionally simple. The focus is not on complex C code, but on learning a clean debugging workflow.

## Bug description

The program stores a small list of devices.

It then searches for a device with a specific ID.

In the buggy version, the requested device does not exist. The search function returns `NULL`, but the program tries to access the device anyway.

This causes a segmentation fault.

## Files

```text
buggy.c   - Program with an intentional NULL pointer dereference
fixed.c   - Corrected version with proper NULL checking
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

## Run the buggy program

```bash
./buggy
```

Expected result:

```text
Looking for device with id 42...
Segmentation fault
```

The exact output may vary depending on your system.

## Debug with GDB

Start GDB:

```bash
gdb ./buggy
```

Inside GDB:

```gdb
run
```

The program should crash with a `SIGSEGV`.

Then inspect the backtrace:

```gdb
bt
```

You should see that the crash happens inside:

```text
print_device_report
```

Inspect the current frame:

```gdb
frame 0
```

Print the pointer value:

```gdb
print device
```

Expected result:

```text
$1 = (DeviceStatus *) 0x0
```

This means `device` is `NULL`.

You can also inspect the source around the crash:

```gdb
list
```

## Root cause

The function `find_device()` returns `NULL` when it does not find a matching device.

In `buggy.c`, the return value is used without checking it:

```c
DeviceStatus *device = find_device(devices, device_count, requested_id);
print_device_report(device);
```

If `device` is `NULL`, calling `print_device_report(device)` leads to invalid memory access.

## Run the fixed program

```bash
./fixed
```

Expected result:

```text
Looking for device with id 42...
Error: device with id 42 was not found.
```

The fixed version checks whether the pointer is `NULL` before using it.

## Clean build files

```bash
make clean
```

## Key lesson

A segmentation fault is often caused by accessing memory that the program does not own.

A good debugging workflow is:

1. Reproduce the crash.
2. Run the program under GDB.
3. Use `bt` to find where it crashed.
4. Inspect variables near the crash.
5. Identify the invalid pointer or invalid memory access.
6. Fix the root cause, not just the symptom.

