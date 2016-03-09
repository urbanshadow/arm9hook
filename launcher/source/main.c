#include <3ds.h>
#include <stdio.h>
#include "payload_bin.h"

void arm9hook_call(const unsigned char *payload,u32 payload_size){
	Handle pxidevHandle;

	if (R_FAILED(srvGetServiceHandle(&pxidevHandle, "pxi:dev"))){
		printf("\x1b[5;0HCouldn't get pxi:dev handle! ");
		return;
	}

	u32 *cmdbuf = getThreadCommandBuffer();
	cmdbuf[0] = IPC_MakeHeader(0x0,0,2); // 0x000010?
	
	cmdbuf[1] = IPC_Desc_PXIBuffer(payload_size, 0, 0); //payload size, 0, 0
	cmdbuf[2] = (u32)payload;

	svcSendSyncRequest(pxidevHandle);
	
	svcCloseHandle(pxidevHandle);

}

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
	
    u32 kDown = 0;
	
	printf("\x1b[0;0HArm9hook by Urbanshadow");
	printf("\x1b[3;0HPress Start to exit.");
    printf("\x1b[2;0HPress A to load an arm9 payload");
    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        kDown = hidKeysDown();

		if (kDown & KEY_A) arm9hook_call(payload_bin,payload_bin_size);
        if (kDown & KEY_START) break; // break in order to return to hbmenu

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    gfxExit();
    return 0;
}
