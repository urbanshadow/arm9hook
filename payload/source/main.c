#include "hid.h"
// bottom1   0x2008CA00-0x200C4E00
// bottom2   0x200C4E00-0x200FD200

void payload(unsigned int *io_buffer)
{	
	unsigned int i;
	unsigned char *bottom = (unsigned char *)0x2008CA00;
	
	for(i=0;i<460800;i=i+3) {
		*(bottom+i) = (char)io_buffer[0];
		*(bottom+i+1) = (char)io_buffer[1];
		*(bottom+i+2) = (char)io_buffer[2];
	}
}