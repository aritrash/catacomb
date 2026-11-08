extern "C" void catacomb_kernel_main();

extern "C" [[noreturn]] void _start() {
    asm volatile("cli");
    catacomb_kernel_main();
    for (;;) asm volatile("hlt");
}
