.section .text
.global loop_3cycles
.type loop_3cycles %function

//Small timing loop to create predictable delays
loop_3cycles:
	SUB R0,#1
	BNE loop_3cycles
	BX LR

