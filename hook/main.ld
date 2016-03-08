ENTRY(_start)
SECTIONS
{
	. = 0x01FFB638;
	.text.start : { *(.text.start) }
	.text : { *(.text) }
	. = ALIGN(4);
}
