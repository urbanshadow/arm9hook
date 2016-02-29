#include "common.h"
#include "draw.h"
#include "i2c.h"
#include "hid.h"

void Reboot()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2);
    while(true);
}


void PowerOff()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while (true);
}

//1. find where pxi:dev is first
//2. pxi:dev cmd handler @ sub_80869F0 (p9, fw 9.9). Search for 0x000101C2 in IDA
int main()
{
    ClearScreenFull(true, true);
	while (true) {
		u32 pad_state = InputWait();
		DrawStringF(3,3,true,"Test 1");
		DrawStringF(16,16,true,"Test 2");
		if (pad_state & BUTTON_START) {
            (pad_state & BUTTON_LEFT) ? Reboot() : PowerOff();
        }
	}
    return 0;
}
