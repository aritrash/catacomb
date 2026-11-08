#pragma once

#include <stdint.h>

namespace catacomb::arch::x86_64 {

void serial_initialize();
void serial_write_char(char character);
void serial_write_string(const char* string);
void serial_write_u64(uint64_t value);
void serial_write_hex(uint64_t value);

}
