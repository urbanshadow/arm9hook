#include "types.h"
#include <stdio.h>
#include <string.h>

/*
Caller
Result ret = 0;
u32 *cmdbuf = getThreadCommandBuffer();
cmdbuf[0] = IPC_MakeHeader(0x6A,0,2); // 0x6A0010?
cmdbuf[1] = IPC_Desc_PXIBuffer(8, 0, 0);
cmdbuf[2] = payloadfile;

if(R_FAILED(ret = svcSendSyncRequest(ampxiHandle)))return ret;

return (Result)cmdbuf[1];
*/
//Callee
//asm("STMFD SP!, {R0-R12,LR}");
//asm("MOV R0,R4");
void arm9hook(u32* cmdbuffer){ 
	memcpy((u32*)cmdbuffer[2],((u32*)0x01FF8000),(cmdbuffer[1] & ~0xFFu) >> 8);
	((void (*)())0x01FF8000)();
}
//asm("LDMFD SP!, {R0-R12,LR}");
int main(){}
