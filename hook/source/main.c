/**
* Arm9hook code
* This should be patched at 0x01FFB69C
* Expected size around 80 to 150 bytes.
**/
#define INSTALL_OK 1
#define DID_NOTHING -1
#define MAX_BYTE_SIZE 13312

int arm9hook(unsigned int* cbuff){
	if((cbuff[0] & 0xFF) == 0x42){
		unsigned int bsize;
		// Grab buffer size from description header
		bsize = ((cbuff[2] & ~0xFFu) >> 8);
		// Check size for install mode
		if(bsize < MAX_BYTE_SIZE){
			// Check for install mode flag
			if(cbuff[1]){
				unsigned int i,*payload,*itcm;
				// Start of unused itcm region
				itcm = (unsigned int*)0x01FF8000;
				// Extract data from command header.
				payload = *(unsigned int**)cbuff[3];
				// Memcpy wannabe
				for(i=0;i<(bsize/4);i++) {
					*(itcm+i) = *(payload+i);
				}
				// Let arm11 code know installation went well.
				return INSTALL_OK;
			}else{
				// Jump to payload assuming a previous install
				unsigned int (*payloadEntry)(unsigned int *) = (void*)0x01FF8000;
				return payloadEntry(*(unsigned int**)cbuff[3]);
			}
		}
	}
	// Let arm11 know nothing happened
	return DID_NOTHING;
}
