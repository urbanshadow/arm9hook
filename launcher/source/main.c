#include <3ds.h>
#include <stdio.h>
#include "a9hook.h"
#include "payload_bin.h"

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
	
    u32 kDown = 0;
	u32 bgr[3] = {0,0,0};
	u8 csel = 0;
	
	printf("\x1b[0;0HArm9hook example by Urbanshadow");
	printf("\x1b[2;0HPress A to check arm9hook");
	printf("\x1b[3;0HPress B to set bottom screen color to:");
	printf("\x1b[4;3H B     G     R");
	printf("\x1b[5;3H%3lu   %3lu   %3lu",bgr[0],bgr[1],bgr[2]);
	printf("\x1b[7;0HPress Start to exit.");
    
    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        kDown = hidKeysDown();

		if (kDown & KEY_A) {
			if(arm9hook_check()){
				printf("\x1b[8;0HARM9 hook is working!");
			}else{
				printf("\x1b[8;0HARM9 hook is not working...");
			}
		}
		if (kDown & KEY_B) {
			arm9hook_call(payload_bin,payload_bin_size,bgr,3);
		}
		if (kDown & KEY_RIGHT) {
			if(csel < 2){
				csel++;
			}
		}
		if (kDown & KEY_LEFT) {
			if(csel > 0){
				csel--;
			}
		}
		if (kDown & KEY_UP) {
			if(bgr[csel] < 255){
				bgr[csel] += 5;
			}
		}
		if (kDown & KEY_DOWN) {
			if(bgr[csel] > 0){
				bgr[csel] -= 5;
			}
		}
        if (kDown & KEY_START) break; // break in order to return to hbmenu
		
		printf("\x1b[5;3H%3lu   %3lu   %3lu",bgr[0],bgr[1],bgr[2]);
		
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    gfxExit();
    return 0;
}
