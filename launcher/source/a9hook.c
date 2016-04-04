#include <3ds.h>
#include <stdio.h>
#include "a9hook.h"
#include "a9hcheck_bin.h"

Result payload_install_run(const u8 *payload,u32 payload_size,u32 *io,u32 io_bytes){
	Handle pxidev;
	if(R_FAILED(srvGetServiceHandle(&pxidev, "pxi:dev"))){
		return (Result)-1;
	}else{
		// Setup our unvalid command header
		u32 *cmdbuf = getThreadCommandBuffer();
		cmdbuf[0] = IPC_MakeHeader(0x0,1,2); // 0x00000042
		
		// Set install flag
		cmdbuf[1] = 1;
		
		// Configure Payload to install
		cmdbuf[2] = IPC_Desc_PXIBuffer(payload_size, 0, IPC_BUFFER_R);
		cmdbuf[3] = (u32)payload;
		
		// Perform install.
		if(R_FAILED(svcSendSyncRequest(pxidev))){
			svcCloseHandle(pxidev);
			return (Result)-2;
		}
		
		// Setup our unvalid command header
		cmdbuf = getThreadCommandBuffer();
		cmdbuf[0] = IPC_MakeHeader(0x0,1,2); // 0x00000042
		
		// Set install flag
		cmdbuf[1] = 0;
		
		// Configure shared memory
		cmdbuf[2] = IPC_Desc_PXIBuffer(io_bytes, 0, IPC_BUFFER_RW);
		cmdbuf[3] = (u32)io;
		
		// Run previously installed payload
		if(R_FAILED(svcSendSyncRequest(pxidev))){
			svcCloseHandle(pxidev);
			return (Result)-3;
		}
		
		svcCloseHandle(pxidev);
		
		return (Result)cmdbuf[1];
	}
}

Result payload_install(const u8 *payload,u32 payload_size){
	Handle pxidev;
	if(R_FAILED(srvGetServiceHandle(&pxidev, "pxi:dev"))){
		return (Result)-1;
	}else{
		// Setup our unvalid command header
		u32 *cmdbuf = getThreadCommandBuffer();
		cmdbuf[0] = IPC_MakeHeader(0x0,1,2); // 0x00000042
		
		// Set install flag
		cmdbuf[1] = 1;
		
		// Configure Payload to install
		cmdbuf[2] = IPC_Desc_PXIBuffer(payload_size, 0, IPC_BUFFER_R);
		cmdbuf[3] = (u32)payload;
		
		// Perform install.
		if(R_FAILED(svcSendSyncRequest(pxidev))){
			svcCloseHandle(pxidev);
			return (Result)-2;
		}
		
		svcCloseHandle(pxidev);
		
		return (Result)cmdbuf[1];
	}
}

Result payload_run(u32 *io_buffer,u32 io_bytes){
	Handle pxidev;
	if(R_FAILED(srvGetServiceHandle(&pxidev, "pxi:dev"))){
		return (Result)-1;
	}else{
		// Setup an unvalid command header
		u32 *cmdbuf = getThreadCommandBuffer();
		cmdbuf[0] = IPC_MakeHeader(0x0,1,2); // 0x00000042
		
		// Unset Install flag
		cmdbuf[1] = 0;
		
		// Configure shared memory
		cmdbuf[2] = IPC_Desc_PXIBuffer(io_bytes, 0, IPC_BUFFER_RW);
		cmdbuf[3] = (u32)io_buffer;
		
		// Call command header.
		if(R_FAILED(svcSendSyncRequest(pxidev))){
			svcCloseHandle(pxidev);
			return (Result)-3;
		}
		
		svcCloseHandle(pxidev);
		
		return (Result)cmdbuf[1];
	}
}

int arm9hook_check(){
	u32 value = 0;
	payload_install_run(a9hcheck_bin,a9hcheck_bin_size,&value,4);
	return value != 0;
}