# Lab 01 — ARM ELF Dynamic Linking

## Objective

Understand the difference between compile-time linking and runtime shared library loading on ARM Linux.

## Environment

- Host: Ubuntu VM (VirtualBox)
- Cross-Toolchain: Crosstool-NG / ARM hard-float / musl
- Target Architecture: ARM 32-bit (EABI5)
- Runtime: QEMU User Mode

## Files

- `main.c`: Main application
- `hello_lib.c`: Shared library implementation
- `lib/libleon_demo.so`: Generated ARM shared library
- `app`: Generated ARM executable

## Build

```bash
CC=arm-training-linux-musleabihf-gcc

$CC -fPIC -shared -o lib/libleon_demo.so hello_lib.c
$CC main.c -L./lib -lleon_demo -o app
```

## ELF Inspection

```bash
file app
readelf -l app | grep interpreter
readelf -d app | grep NEEDED
```

Observed:

- ELF32 / ARM / EABI5
- Interpreter: `/lib/ld-musl-armhf.so.1`
- NEEDED: `libleon_demo.so`

## Runtime Tests

| Test | Condition | Result |
|---|---|---|
| A | No custom library path | PASS — Expected loading failure |
| B | Correct LD_LIBRARY_PATH | PASS — Application executed |
| C | Invalid LD_LIBRARY_PATH | PASS — Expected loading failure |

Successful output:

```text
Hello from ARM shared library!
```

## Key Findings

1. Successful linking does not guarantee successful execution.
2. `DT_NEEDED` records shared library dependencies.
3. The ELF interpreter identifies the runtime dynamic loader.
4. `LD_LIBRARY_PATH` affects runtime library lookup.
5. Missing shared libraries can cause symbol resolution failures.

## Status

**PASS — 2026-10-19**

All three runtime tests produced the expected results.
