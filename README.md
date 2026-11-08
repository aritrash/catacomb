# Project Catacomb

An experimental x86-64 operating system written primarily in C++20, with architecture-specific assembly.

## Architecture

| Component | Technology |
|---|---|
| Architecture | x86-64 |
| Kernel | Modular Monolithic |
| Primary Language | C++20 |
| Assembly | NASM |
| Bootloader | Limine |
| Build System | CMake + Ninja |
| Emulator | QEMU |

## Development Status

### M0 — Boot Foundation: COMPLETED

Catacomb has successfully booted as a freestanding x86-64 kernel through Limine in a UEFI environment.

Verified capabilities:

- Freestanding C++20 kernel compilation.
- Custom higher-half ELF linker layout.
- Limine boot protocol integration (base revision 6).
- COM1 serial output.
- Higher Half Direct Map (HHDM) discovery.
- Physical memory map discovery.
- Framebuffer discovery.
- Hybrid BIOS/UEFI ISO generation.
- Successful QEMU/KVM boot.

### Current Boot Environment

- Limine: 12.9.6
- Cross-compiler: GCC 16.2.0
- QEMU: 10.2.1
- Firmware: OVMF UEFI

## Design Principles

- Architectural correctness before feature accumulation.
- Explicit subsystem interfaces.
- Predictable memory management.
- Minimal external dependencies.
- Incremental implementation and verification.

## Planned Subsystems

- GDT and IDT
- Physical Memory Manager
- Virtual Memory Manager
- Kernel Heap
- Framebuffer Console
- Interrupt and Timer Infrastructure
- Multitasking and ITAS
- Gravekeeper Resource Management

## Project Philosophy

Catacomb is an experimental systems engineering project. Its development prioritizes understanding, architectural rigor, reproducibility, and incremental validation.
