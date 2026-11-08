#pragma once

#include <stdint.h>

namespace catacomb::core::log {

enum class Level : uint8_t {
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

using Sink = void (*)(char);

void initialize(Sink sink);
void write(Level level, const char* message);
void write_u64(Level level, const char* label, uint64_t value);
void write_hex(Level level, const char* label, uint64_t value);

}
