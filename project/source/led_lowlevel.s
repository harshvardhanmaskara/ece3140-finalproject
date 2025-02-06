/*
 * led_lowlevel.s
 *
 *  Created on: Mar 02, 2024
 *      Author: hm475
 */

.section .text
.global set_led
.type set_led %function

.equ MASK, 8388608
.equ PSOR, 0x400FF104
.equ PCOR, 0x400FF108
.equ FILLER_MASK, 0x00FFFFFF

set_led:
	PUSH {R4, R5, R6, R7, LR}
	LDR R1, =MASK//1 followed by 23 zeroes
	MOV R2, #8//LED signal
	LDR R3, =PSOR
	LDR R4, =PCOR
	MOV R5, R0//copy
	MOV R6, #24//counter
	LDR R7, =FILLER_MASK//Dealing with filler bits. Noticed filler bits fluctuating
	//between insignificant 0s and non zero values too, so doing the step below makes
	//sure that it does not affect the signal.
	AND R5, R7

extract_bits:
	SUB R6, #1
	TST R1, R5
	BEQ bit_zero
	B bit_one

bit_one:
	STR R2, [R3]//9-15 cycles
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	STR R2, [R4]//9-15 cycles
	B check

bit_zero:
	STR R2, [R3]//4 cycles
	NOP
	STR R2, [R4]//9-15 cycles
	B check

check:
	CMP R6, #0
	BEQ end
	LSR R1, #1
	B extract_bits

end:
	POP {R4, R5, R6, R7, PC}
