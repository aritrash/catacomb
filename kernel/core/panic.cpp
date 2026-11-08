#include <catacomb/core/panic.hpp>
#include <catacomb/core/log.hpp>
#include <catacomb/arch/x86_64/cpu.hpp>

namespace catacomb::core {

[[noreturn]] void panic(const char* reason) {
    arch::x86_64::cpu::disable_interrupts();
    log::write(log::Level::Fatal, "========================================");
    log::write(log::Level::Fatal, "          CATACOMB KERNEL PANIC");
    log::write(log::Level::Fatal, "========================================");
    log::write(log::Level::Fatal, reason ? reason : "Unknown kernel failure.");
    log::write(log::Level::Fatal, "Execution cannot continue.");
    log::write(log::Level::Fatal, "Processor halted.");
    arch::x86_64::cpu::halt_forever();
}

}
