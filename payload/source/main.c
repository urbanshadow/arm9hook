#include "hid.h"
//		bottom1   0x2008CA00-0x200C4E00
//		bottom2   0x200C4E00-0x200FD200

void __attribute__((section (".text.start"),naked)) _start()
{
	__asm__("STMFD SP!,{LR}");
	unsigned int i;
	unsigned char *bottom = (unsigned char *)0x2008CA00;
	for(i=0;i<460800;i=i+3) {
		*(bottom+i) = 255;
		*(bottom+i+1) = 255;
		*(bottom+i+2) = 255;
	}
    __asm__("LDMFD SP!,{PC}");
}

