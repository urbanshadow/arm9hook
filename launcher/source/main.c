#include <3ds.h>
#include <stdio.h>
#include "a9hook.h"
#include "payload_bin.h"

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
	
    u32 kDown = 0;
	u8 installed = 0;
	u32 runs = 0;
	u32 bgr[3] = {255,128,0};
	
	printf("\x1b[0;0HArm9hook example by Urbanshadow");
	printf("\x1b[2;0HPress A to check arm9hook");
	printf("\x1b[3;0HPress B to run the payload");
	printf("\x1b[7;0HPress Start to exit.");
    
    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        kDown = hidKeysDown();

		if (kDown & KEY_A) {
			installed = 0;
			if(arm9hook_check()){
				printf("\x1b[4;0HHook detected!        ");
			}else{
				printf("\x1b[4;0HHook not found...     ");
			}	
		}
		if (kDown & KEY_B) {
			if(installed){
				payload_run(bgr,12);
				runs++;
				printf("\x1b[5;0HRuns:%lu",runs);
			}else{
				payload_install(payload_bin,payload_bin_size);
				installed = 1;
				printf("\x1b[4;0HPayload Installed!");
			}
		}
        if (kDown & KEY_START) break; // break in order to return to hbmenu
		
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
	
    gfxExit();
    return 0;
}
