.section .text.start
.arm
.global _start
_start:
MOV R0,R4
BL arm9hook
LDR R1, =0x00041
STR R1, [R4], #4
STMIA R4, {R0,R5}
ADD SP, SP, #0x84
LDMFD SP!,{R4-R11,PC}