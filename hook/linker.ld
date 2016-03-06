ENTRY(_start)
SECTIONS
{
    .text.start : { *(.text.start) }
    . = ALIGN(4);
}
