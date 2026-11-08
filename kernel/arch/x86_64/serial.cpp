#include <catacomb/arch/x86_64/serial.hpp>

namespace catacomb::arch::x86_64 {

static constexpr uint16_t COM1 = 0x3F8;

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void serial_initialize() {
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

void serial_write_char(char character) {
    for (uint32_t timeout = 0; timeout < 1000000; ++timeout) {
        if (inb(COM1 + 5) & 0x20) {
            outb(COM1, static_cast<uint8_t>(character));
            return;
        }
    }
}

void serial_write_string(const char* string) {
    if (!string) return;
    while (*string) {
        if (*string == '\n') serial_write_char('\r');
        serial_write_char(*string++);
    }
}

void serial_write_u64(uint64_t value) {
    char buffer[21];
    uint32_t index = 0;
    do {
        buffer[index++] = static_cast<char>('0' + value % 10);
        value /= 10;
    } while (value);
    while (index) serial_write_char(buffer[--index]);
}

void serial_write_hex(uint64_t value) {
    static constexpr char digits[] = "0123456789ABCDEF";
    serial_write_string("0x");
    for (int shift = 60; shift >= 0; shift -= 4) {
        serial_write_char(digits[(value >> shift) & 0xF]);
    }
}

}
