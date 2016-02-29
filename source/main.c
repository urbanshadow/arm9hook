typedef unsigned int u32;
__asm__("STMFD SP!,{R0-R11,LR}");
__asm__("MOV R0,R4");
__attribute__((naked)) void pyldcpy(u32 *s1,const u32 *s2,u32 size){
	int i;
	for(i=0;i<(size/4);i++) *(s1+i) = *(s2+i);
}
__attribute__((naked)) void arm9hook(u32* cmdbuffer){ 
	pyldcpy(((u32*)0x01FF8000),(u32*)cmdbuffer[2],(cmdbuffer[1] & ~0xFFu) >> 8);
	((void (*)())0x01FF8000)();
}
__asm__("LDMFD SP!,{R0-R11,LR}");
int main(){}