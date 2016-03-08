/**
* Arm9hook code
* This should be patched at 0x01FFB69C
* Expected size around 80 to 100 bytes.
**/

void arm9hook(unsigned int* cbuff){
	unsigned int i,paysize,*payload,*itcm;
	
	paysize = ((cbuff[1] & ~0xFFu) >> 8);
	itcm = (unsigned int*)0x01FF8000; //Start of unused itcm region
	payload = *(unsigned int**)cbuff[2]; //payload pointer from the command header
	
	// Memcpy wannabe
	for(i=0;i<(paysize/4);i++) {
		*(itcm+i) = *(payload+i);
	}
	
	// Jump to payload after copy
	void(*payloadEntry)() = (void*)0x01FF8000;
	payloadEntry();
}
