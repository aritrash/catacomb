#pragma once

#include <catacomb/core/panic.hpp>

#define CATACOMB_ASSERT(condition, message) do { if (!(condition)) ::catacomb::core::panic(message); } while (false)
