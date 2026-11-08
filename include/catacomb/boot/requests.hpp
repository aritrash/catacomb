#pragma once

#include <catacomb/limine.h>

extern "C" {
    extern volatile uint64_t catacomb_base_revision[3];
    extern volatile struct limine_hhdm_request catacomb_hhdm_request;
    extern volatile struct limine_framebuffer_request catacomb_framebuffer_request;
    extern volatile struct limine_memmap_request catacomb_memmap_request;
}
