OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

PHDRS
{
    requests PT_LOAD FLAGS(6);
    text     PT_LOAD FLAGS(5);
    rodata   PT_LOAD FLAGS(4);
    data     PT_LOAD FLAGS(6);
    stack    PT_GNU_STACK FLAGS(6);
}

SECTIONS
{
    . = 0xffffffff80000000;
    __kernel_start = .;

    .limine_requests : ALIGN(8)
    {
        __limine_requests_start = .;
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))
        __limine_requests_end = .;
    } :requests

    . = ALIGN(0x1000);
    __text_start = .;

    .text :
    {
        *(.text .text.*)
    } :text

    __text_end = .;

    . = ALIGN(0x1000);
    __rodata_start = .;

    .rodata :
    {
        *(.rodata .rodata.*)
    } :rodata

    __rodata_end = .;

    . = ALIGN(0x1000);
    __data_start = .;

    .data :
    {
        *(.data .data.*)
    } :data

    .bss (NOLOAD) :
    {
        *(COMMON)
        *(.bss .bss.*)
    } :data

    __data_end = .;
    __kernel_end = .;

    /DISCARD/ :
    {
        *(.eh_frame*)
        *(.gcc_except_table*)
        *(.note*)
        *(.comment)
    }
}
