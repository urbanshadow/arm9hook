#include "hid.h"
// bottom1   0x2008CA00-0x200C4E00
// bottom2   0x200C4E00-0x200FD200

int payload(unsigned int *col)
{	
	unsigned int i;
	unsigned char *bottom = (unsigned char *)0x2008CA00;
	
	for(i=0;i<460800;i=i+3) {
		*(bottom+i) = (unsigned char)col[1];
		*(bottom+i+1) = (unsigned char)col[2];
		*(bottom+i+2) = (unsigned char)col[3];
	}
	
	return 0;
}