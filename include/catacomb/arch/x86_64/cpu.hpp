#pragma once

namespace catacomb::arch::x86_64::cpu {

inline void disable_interrupts() {
    asm volatile("cli" ::: "memory");
}

inline void enable_interrupts() {
    asm volatile("sti" ::: "memory");
}

inline void halt() {
    asm volatile("hlt" ::: "memory");
}

[[noreturn]] inline void halt_forever() {
    disable_interrupts();
    for (;;) halt();
}

}
