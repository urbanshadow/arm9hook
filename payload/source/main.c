#include "hid.h"
//		bottom1   0x2008CA00-0x200C4E00
//		bottom2   0x200C4E00-0x200FD200
void printcolor(unsigned char b,unsigned char g,unsigned char r) {
	unsigned int i;
	unsigned char *bottom = (unsigned char *)0x2008CA00;
	for(i=0;i<460800;i=i+3) {
		*(bottom+i) = b;
		*(bottom+i+1) = g;
		*(bottom+i+2) = r;
	}
}

void __attribute__((section (".text.start"),naked)) _start()
{
	__asm__("STMFD SP!,{LR}");
	printcolor(255,255,255);
    __asm__("LDMFD SP!,{PC}");
}

