#include "hid.h"
//		bottom1   0x2008CA00-0x200C4E00
//		bottom2   0x200C4E00-0x200FD200
void _start()
{
	unsigned int pad_state_old = HID_STATE;
    unsigned int pad_state = pad_state_old;
	unsigned int i;
	while (1) {
        pad_state = HID_STATE;
        if (pad_state ^ pad_state_old)
            pad_state = ~pad_state;
		for(i=0;i<460800;i++)
			*(((unsigned int *)0x2008CA00)+i) = 0xFFFF;
		if (pad_state & BUTTON_B) break;
	}
    return;
}
