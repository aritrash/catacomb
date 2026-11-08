#include <catacomb/boot/requests.hpp>

extern "C" {

__attribute__((used, section(".limine_requests_start"), aligned(8)))
volatile uint64_t catacomb_limine_requests_start[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests"), aligned(8)))
volatile uint64_t catacomb_base_revision[3] = LIMINE_BASE_REVISION(6);

__attribute__((used, section(".limine_requests"), aligned(8)))
volatile struct limine_hhdm_request catacomb_hhdm_request = {
    .id = LIMINE_HHDM_REQUEST_ID,
    .revision = 0,
    .response = nullptr
};

__attribute__((used, section(".limine_requests"), aligned(8)))
volatile struct limine_framebuffer_request catacomb_framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
    .response = nullptr
};

__attribute__((used, section(".limine_requests"), aligned(8)))
volatile struct limine_memmap_request catacomb_memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0,
    .response = nullptr
};

__attribute__((used, section(".limine_requests_end"), aligned(8)))
volatile uint64_t catacomb_limine_requests_end[] = LIMINE_REQUESTS_END_MARKER;

}
