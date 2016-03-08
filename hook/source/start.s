.section .text.start
.arm
.global _start
_start:
b wrap
return:
.word 0xDEADBEEF

wrap:
STMFD SP!,{R0-R12,LR}
MOV R0,R4
BL arm9hook
LDMFD SP!,{R0-R12,LR}
ldr PC,return
