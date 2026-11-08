cmake_minimum_required(VERSION 3.25)

project(Catacomb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(KERNEL_SOURCES
    kernel/arch/x86_64/entry.cpp
    kernel/arch/x86_64/limine_requests.cpp
    kernel/arch/x86_64/serial.cpp
    kernel/core/kernel.cpp
)

add_executable(catacomb ${KERNEL_SOURCES})

target_include_directories(catacomb PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

target_compile_options(catacomb PRIVATE
    -ffreestanding
    -fno-builtin
    -fno-stack-protector
    -fno-exceptions
    -fno-rtti
    -fno-pic
    -fno-pie
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
    -fno-threadsafe-statics
    -mno-red-zone
    -mcmodel=kernel
    -mno-mmx
    -mno-sse
    -mno-sse2
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
)

target_link_options(catacomb PRIVATE
    -nostdlib
    -static
    -no-pie
    -Wl,--gc-sections
    -Wl,--no-undefined
    -Wl,--build-id=none
    -Wl,-z,max-page-size=0x1000
    -Wl,-z,noexecstack
    "-Wl,-T,${CMAKE_SOURCE_DIR}/linker.ld"
    "-Wl,-Map=${CMAKE_BINARY_DIR}/catacomb.map"
)

target_link_libraries(catacomb PRIVATE gcc)

set_target_properties(catacomb PROPERTIES
    OUTPUT_NAME catacomb
    SUFFIX ".elf"
    LINK_DEPENDS "${CMAKE_SOURCE_DIR}/linker.ld"
)
