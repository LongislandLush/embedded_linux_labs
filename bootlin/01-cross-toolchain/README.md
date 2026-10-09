# Lab 01 — ARM Cross-Compilation Toolchain

## Objective

Build an ARM Linux cross-compilation toolchain for the BeagleBone Black using crosstool-NG, then verify the generated ARM executable with QEMU User-mode emulation.

## Environment

| Component | Configuration |
|---|---|
| Host | Ubuntu 24.04 x86-64 (VirtualBox) |
| Target | BeagleBone Black, ARM Cortex-A8 |
| crosstool-NG | 1.28.0 |
| GCC | 15.2.0 |
| C Library | musl 1.2.5 |
| Linux Headers | 6.5.13 |
| Floating Point | VFPv3, Hard-Float ABI |
| Toolchain Tuple | arm-training-linux-musleabihf |

## Build

```bash
./ct-ng arm-cortex_a8-linux-gnueabi
./ct-ng menuconfig
./ct-ng build
```

The toolchain was installed in `~/x-tools/arm-training-linux-musleabihf/`.

## Verification

Add the compiler to PATH:

```bash
export PATH="$HOME/x-tools/arm-training-linux-musleabihf/bin:$PATH"
```

Compile the test application:

```bash
arm-linux-gcc -o hello hello.c
file hello
readelf -h hello
readelf -A hello
```

Verified results:

- ELF32, ARM architecture
- EABI5, Hard-Float ABI
- VFP register arguments

Run with QEMU:

```bash
qemu-arm -L \
  "$HOME/x-tools/arm-training-linux-musleabihf/arm-training-linux-musleabihf/sysroot" \
  hello
```

Output:

```text
Hello world!
```

## Troubleshooting

**Compiler not found:** Add the toolchain's `bin` directory to `PATH`.

**Missing musl loader:** Use QEMU's `-L` option to specify the ARM sysroot.

**Incorrect GCC options:** `-c` compiles without linking; `-o` specifies the output filename.

## Lessons Learned

- Cross-compilation between x86-64 and ARM
- C preprocessing, compilation, assembly, and linking
- ELF executable and relocatable object files
- ARM EABI and Hard-Float ABI
- Dynamic linking and the musl loader
- QEMU User-mode emulation
