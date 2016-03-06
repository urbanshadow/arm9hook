/**
* Arm9hook code
* This should be patched at 0x01FFB69C
* Expected size around 80 to 100 bytes.
**/

// ARM ASM Entry
void __attribute__((section (".text.start"),naked)) _start(void){
	__asm__("STMFD SP!,{R0-R12,LR}\n"
	"MOV R0,R4\n"
	"STMFD SP!,{PC}\n" // Pc push to return later to it
	"B arm9hook\n" 
	"LDMFD SP!,{R0-R12,LR}\n"
	"LDR PC,[PC,#-4]\n"
	".word 0xDEADBEEF"); // This will be patched afterwards to firm dependant return position.
}

void __attribute__((naked)) arm9hook(unsigned int* cbuff){
	unsigned int i,paysize,*payload,*itcm;
	
	paysize = ((cbuff[1] & ~0xFFu) >> 8);
	itcm = (unsigned int*)0x01FF8000; //Start of unused itcm region
	payload = (unsigned int*)cbuff[2]; //payload pointer from the command header
	
	// Memcpy wannabe
	for(i=0;i<(paysize/4);i++) {
		*(itcm+i) = *(payload+i);
	}
	
	// Jump to payload after copy
	((void (*)())0x01FF8000)();
}


