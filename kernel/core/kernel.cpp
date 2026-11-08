#include <catacomb/boot/requests.hpp>
#include <catacomb/arch/x86_64/serial.hpp>

using namespace catacomb::arch::x86_64;

extern "C" [[noreturn]] void catacomb_kernel_main() {
    serial_initialize();

    serial_write_string("\n");
    serial_write_string("========================================\n");
    serial_write_string("          CATACOMB OPERATING SYSTEM      \n");
    serial_write_string("========================================\n");

    serial_write_string("[BOOT] Kernel entry reached.\n");

    if (!LIMINE_BASE_REVISION_SUPPORTED(catacomb_base_revision)) {
        serial_write_string("[FATAL] Required Limine base revision unsupported.\n");
        for (;;) asm volatile("hlt");
    }

    serial_write_string("[BOOT] Limine base revision 6: supported.\n");

    if (!catacomb_hhdm_request.response) {
        serial_write_string("[FATAL] HHDM response unavailable.\n");
        for (;;) asm volatile("hlt");
    }

    serial_write_string("[MEMORY] HHDM offset: ");
    serial_write_hex(catacomb_hhdm_request.response->offset);
    serial_write_string("\n");

    if (!catacomb_memmap_request.response) {
        serial_write_string("[FATAL] Memory map response unavailable.\n");
        for (;;) asm volatile("hlt");
    }

    auto* memory_map = catacomb_memmap_request.response;

    uint64_t usable_memory = 0;
    uint64_t usable_regions = 0;

    for (uint64_t i = 0; i < memory_map->entry_count; ++i) {
        auto* entry = memory_map->entries[i];
        if (!entry || entry->type != LIMINE_MEMMAP_USABLE) continue;
        if (UINT64_MAX - usable_memory < entry->length) {
            usable_memory = UINT64_MAX;
            break;
        }
        usable_memory += entry->length;
        ++usable_regions;
    }

    serial_write_string("[MEMORY] Memory map entries: ");
    serial_write_u64(memory_map->entry_count);
    serial_write_string("\n");

    serial_write_string("[MEMORY] Usable regions: ");
    serial_write_u64(usable_regions);
    serial_write_string("\n");

    serial_write_string("[MEMORY] Total usable memory: ");
    serial_write_u64(usable_memory / (1024 * 1024));
    serial_write_string(" MiB\n");

    if (!catacomb_framebuffer_request.response || !catacomb_framebuffer_request.response->framebuffer_count) {
        serial_write_string("[VIDEO] Framebuffer unavailable.\n");
    } else {
        auto* framebuffer = catacomb_framebuffer_request.response->framebuffers[0];
        if (!framebuffer) {
            serial_write_string("[VIDEO] Invalid framebuffer response.\n");
        } else {
            serial_write_string("[VIDEO] Framebuffer detected: ");
            serial_write_u64(framebuffer->width);
            serial_write_string(" x ");
            serial_write_u64(framebuffer->height);
            serial_write_string(" @ ");
            serial_write_u64(framebuffer->bpp);
            serial_write_string(" bpp\n");
        }
    }

    serial_write_string("\n");
    serial_write_string("[BOOT] CATACOMB KERNEL INITIALIZED.\n");
    serial_write_string("[BOOT] System halted. Further initialization pending.\n");

    for (;;) asm volatile("hlt");
}
