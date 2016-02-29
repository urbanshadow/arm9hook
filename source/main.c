typedef unsigned int u32;
/* Caller:
Result ret = 0;
u32 *cmdbuf = getThreadCommandBuffer();
cmdbuf[0] = IPC_MakeHeader(0x6A,0,2); // 0x6A0010?
cmdbuf[1] = IPC_Desc_PXIBuffer(8, 0, 0);
cmdbuf[2] = payloadfile;

if(R_FAILED(ret = svcSendSyncRequest(ampxiHandle)))return ret;

return (Result)cmdbuf[1];
*/
//Callee:
__asm__("STMFD SP!,{R0-R12,LR}");
__asm__("MOV R0,R4");
__attribute__((naked)) void arm9hook(u32* cmdbuffer){
	u32 i;
	for(i=0;i<(((cmdbuffer[1] & ~0xFFu) >> 8)/4);i++) *(((u32*)0x01FF8000)+i) = *(((u32*)cmdbuffer[2])+i);
	((void (*)())0x01FF8000)();
}
int main(){}
__asm__("LDMFD SP!,{R0-R12,LR}");