#include <3ds.h>
#include <stdio.h>
#include "a9hook.h"
#include "a9hcheck_bin.h"

void arm9hook_call(const u8 *payload,u32 payload_size,u32 *io_buffer,u32 io_size){
	Handle pxidevHandle;

	// Test PXI:DEV permissions
	if (R_FAILED(srvGetServiceHandle(&pxidevHandle, "pxi:dev"))){
		printf("\x1b[5;0HCouldn't get pxi:dev handle! ");
		return;
	}

	// Setup an unvalid command header
	u32 *cmdbuf = getThreadCommandBuffer();
	cmdbuf[0] = IPC_MakeHeader(0x0,0,4); // 0x000004?
	
	// Configure Payload
	cmdbuf[1] = IPC_Desc_PXIBuffer(payload_size, 0, IPC_BUFFER_R); //payload size, 0, 0
	cmdbuf[2] = (u32)payload;
	
	// Configure shared memory
	cmdbuf[3] = IPC_Desc_PXIBuffer(io_size*4, 1, IPC_BUFFER_RW);
	cmdbuf[4] = (u32)io_buffer;
	
	// Call command header.
	svcSendSyncRequest(pxidevHandle);
	
	// Safely close request and go back.
	svcCloseHandle(pxidevHandle);
}

int arm9hook_check(){
	u32 value = 0;
	arm9hook_call(a9hcheck_bin,a9hcheck_bin_size,&value,1);
	return value != 0;
}