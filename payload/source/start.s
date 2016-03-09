.section .text.start
.arm
.global _start
_start:
b wrap

wrap:
STMFD SP!,{LR}
BL payload
LDMFD SP!,{PC}
