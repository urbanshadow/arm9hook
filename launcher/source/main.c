#include <3ds.h>
#include <stdio.h>

unsigned char payld[] = {
	56,48,159,229,4,224,45,229,3,224,160,225,48,16,159,229,0,192,147,229,
	44,32,159,229,0,0,158,229,40,48,159,229,0,0,92,225,0,0,224,17,4,16,163,
	229,2,0,83,225,252,255,255,26,2,0,16,227,246,255,255,10,4,240,157,228,
	0,96,20,16,255,255,0,0,252,233,36,32,252,201,8,32
};

void arm9hook_call(void *payload,u32 payload_size){
	Handle pxidevHandle;

	if (R_FAILED(srvGetServiceHandle(&pxidevHandle, "pxi:dev"))){
		printf("\x1b[5;0HCouldn't get pxi:dev handle! ");
		return;
	}

	u32 *cmdbuf = getThreadCommandBuffer();
	cmdbuf[0] = IPC_MakeHeader(0x0,0,2); // 0x000010?
	
	cmdbuf[1] = IPC_Desc_PXIBuffer(payload_size, 0, 0); //payload size, 0, 0
	cmdbuf[2] = (u32)payload;

	printf("\x1b[5;0H%ld",svcSendSyncRequest(pxidevHandle));
	printf("\x1b[5;10H%ld",cmdbuf[1]);
	
	svcCloseHandle(pxidevHandle);

}

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
	
    u32 kDown = 0;
	
	printf("\x1b[0;0HArm9hook test by Urbanshadow");
	printf("\x1b[3;0HPress Start to exit.");
    printf("\x1b[2;0HPress A to load an arm9 payload");
    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        kDown = hidKeysDown();

		if (kDown & KEY_A) arm9hook_call(payld,80); //TODO: file loading, then arm9hook_call();
        if (kDown & KEY_START) break; // break in order to return to hbmenu

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    gfxExit();
    return 0;
}
