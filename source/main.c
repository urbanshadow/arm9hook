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

/**
* Arm9hook code
* This should be patched at 0x01FFB69C
* Expected size around 80 to 100 bytes.
**/

void __attribute__((naked)) arm9hook(u32* cbuff){
	u32 i,paysize,*payload,*itcm;
	
	paysize = ((cbuff[1] & ~0xFFu) >> 8);
	itcm = (u32*)0x01FF8000; //Start of unused itcm region
	payload = (u32*)cbuff[2]; //payload pointer from the command header
	
	// Memcpy wannabe
	for(i=0;i<(paysize/4);i++) {
		*(itcm+i) = *(payload+i);
	}
	
	// Jump to payload after copy
	((void (*)())0x01FF8000)();
}

// ARM ASM Entry
void __attribute__((naked)) _start(void){
	__asm__("STMFD SP!,{R0-R12,LR}\n"
	"MOV R0,R4\n"
	"BLX arm9hook\n" //BLX stores this address in LR
	"LDMFD SP!,{R0-R12,LR}\n");
}
