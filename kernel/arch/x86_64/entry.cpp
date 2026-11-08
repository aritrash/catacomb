#include <catacomb/arch/x86_64/cpu.hpp>

extern "C" void catacomb_kernel_main();

extern "C" [[noreturn]] void _start() {
    catacomb::arch::x86_64::cpu::disable_interrupts();
    catacomb_kernel_main();
    catacomb::arch::x86_64::cpu::halt_forever();
}
