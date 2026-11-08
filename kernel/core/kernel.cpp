#include <catacomb/boot/requests.hpp>
#include <catacomb/arch/x86_64/serial.hpp>
#include <catacomb/core/log.hpp>
#include <catacomb/core/panic.hpp>
#include <catacomb/core/assert.hpp>
#include <catacomb/arch/x86_64/cpu.hpp>

using namespace catacomb::core;
using namespace catacomb::core::log;
using namespace catacomb::arch::x86_64;

extern "C" [[noreturn]] void catacomb_kernel_main() {
    serial_initialize();
    log::initialize(serial_write_char);

    log::write(Level::Info, "Catacomb kernel entry reached.");
    log::write(Level::Info, "Initializing kernel housekeeping.");

    if (!LIMINE_BASE_REVISION_SUPPORTED(catacomb_base_revision)) panic("Required Limine base revision unsupported.");

    log::write(Level::Info, "Limine base revision 6 supported.");

    CATACOMB_ASSERT(catacomb_hhdm_request.response, "HHDM response unavailable.");
    log::write_hex(Level::Info, "HHDM offset: ", catacomb_hhdm_request.response->offset);

    CATACOMB_ASSERT(catacomb_memmap_request.response, "Memory map response unavailable.");

    auto* memory_map = catacomb_memmap_request.response;
    uint64_t usable_memory = 0;
    uint64_t usable_regions = 0;

    for (uint64_t i = 0; i < memory_map->entry_count; ++i) {
        auto* entry = memory_map->entries[i];
        if (!entry || entry->type != LIMINE_MEMMAP_USABLE) continue;
        if (UINT64_MAX - usable_memory < entry->length) panic("Physical memory size calculation overflow.");
        usable_memory += entry->length;
        ++usable_regions;
    }

    log::write_u64(Level::Info, "Memory map entries: ", memory_map->entry_count);
    log::write_u64(Level::Info, "Usable regions: ", usable_regions);
    log::write_u64(Level::Info, "Total usable memory (MiB): ", usable_memory / (1024 * 1024));

    if (!catacomb_framebuffer_request.response || !catacomb_framebuffer_request.response->framebuffer_count) {
        log::write(Level::Warning, "Framebuffer unavailable.");
    } else {
        auto* framebuffer = catacomb_framebuffer_request.response->framebuffers[0];
        CATACOMB_ASSERT(framebuffer, "Invalid framebuffer response.");
        log::write_u64(Level::Info, "Framebuffer width: ", framebuffer->width);
        log::write_u64(Level::Info, "Framebuffer height: ", framebuffer->height);
        log::write_u64(Level::Info, "Framebuffer bits per pixel: ", framebuffer->bpp);
    }

    log::write(Level::Info, "Kernel housekeeping initialized.");
    log::write(Level::Info, "CATACOMB KERNEL INITIALIZED.");
    catacomb::arch::x86_64::cpu::halt_forever();
}
