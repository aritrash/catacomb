#include <catacomb/core/log.hpp>

namespace catacomb::core::log {

static Sink output_sink = nullptr;

static const char* level_name(Level level) {
    switch (level) {
        case Level::Debug: return "DEBUG";
        case Level::Info: return "INFO";
        case Level::Warning: return "WARNING";
        case Level::Error: return "ERROR";
        case Level::Fatal: return "FATAL";
        default: return "UNKNOWN";
    }
}

static void emit_char(char character) {
    if (output_sink) output_sink(character);
}

static void emit_string(const char* string) {
    if (!string) return;
    while (*string) emit_char(*string++);
}

static void emit_newline() {
    emit_char('\r');
    emit_char('\n');
}

static void emit_prefix(Level level) {
    emit_char('[');
    emit_string(level_name(level));
    emit_string("] ");
}

static void emit_u64(uint64_t value) {
    char buffer[20];
    uint32_t index = 0;
    do {
        buffer[index++] = static_cast<char>('0' + value % 10);
        value /= 10;
    } while (value);
    while (index) emit_char(buffer[--index]);
}

static void emit_hex(uint64_t value) {
    static constexpr char digits[] = "0123456789ABCDEF";
    emit_string("0x");
    for (int shift = 60; shift >= 0; shift -= 4) emit_char(digits[(value >> shift) & 0xF]);
}

void initialize(Sink sink) {
    output_sink = sink;
}

void write(Level level, const char* message) {
    if (!output_sink) return;
    emit_prefix(level);
    emit_string(message);
    emit_newline();
}

void write_u64(Level level, const char* label, uint64_t value) {
    if (!output_sink) return;
    emit_prefix(level);
    emit_string(label);
    emit_u64(value);
    emit_newline();
}

void write_hex(Level level, const char* label, uint64_t value) {
    if (!output_sink) return;
    emit_prefix(level);
    emit_string(label);
    emit_hex(value);
    emit_newline();
}

}
