#include "hid.h"
// bottom1   0x2008CA00-0x200C4E00
// bottom2   0x200C4E00-0x200FD200

void payload()
{
	unsigned int i,door;
	unsigned int pad_state_old = HID_STATE;
	unsigned int pad_state = pad_state_old;
	unsigned char *bottom = (unsigned char *)0x2008CA00;
	
	while (1) {
		if (pad_state ^ pad_state_old)
			pad_state = ~pad_state;
		if (pad_state & BUTTON_B) break;
		pad_state = HID_STATE;
	}
	
	for(i=0;i<460800;i=i+3) {
		*(bottom+i) = 255;
		*(bottom+i+1) = 128;
		*(bottom+i+2) = 0;
	}
}