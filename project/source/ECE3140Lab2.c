/*
 * ECE3140Lab2.c
 *
 * Nils Napp
 * Cornell University
 * All right reserved
 *
 * Jan 2024
 * Ithaca NY
 *
 * This file is part of the ECE3140/CS3420 offering for Spring 2024. If you are
 * not part of this class, you should not have access to this file. Do not post,
 * share, or otherwise distribute this file. We will consider it an AI violation 
 * if you do.
 */

#include "ECE3140Lab2.h"
#include <MKL46Z4.h>

void set15MHz(void){
	/* The clock generation options for this chip are
	 * somewhat complicated with many options for different
	 * internal/external clock sources that get
	 * multiplied and divided by either a frequency
	 * locked loop (FLL) or a phase locked loop (PLL).
	 *
	 * This configuration is for:
	 * External 8MHz oscillator as we have on our FRDMKL46z board
	 * PLL for generating a 15MHz System core and bus clock
	 *
	 * If you'd like to dig into the manual, this mode is
	 * named PEE. Since only certain transitions between
	 * operating modes are allowed this code makes the
	 * following transitions to get to PEE.
	 *
	 * FEI -1-> FBE -2-> PBE -3-> PEE (8MHz /4 *30)
	 *
	 * Then set the SIM divider to 4 and 1 to get a
	 * 60MHz/4 = 15MHz core clock
	 * 15MHz/1 = 15MHz bus clock
	 */

	/* Transition: FEI -1-> FBE
	 * Switch to bypass mode from regular FLL mode
	 *
	 * The following options are set:
	 * RANGE0 for 8-32MHz
	 * HGO0 for low-power (not high-gain) operation
	 * EREFS0 for external oscillator
	 * CLKS for external clock source
	 * FRDIV for 8MHz/256 -> 31.2 kHz (in required range for FLL)
	 * IREFS enable external oscillator
	 */

	MCG->C2 = MCG_C2_RANGE0(0b10) | MCG_C2_HGO0(0) | MCG_C2_EREFS0(1);
	MCG->C1 = MCG_C1_CLKS(0b10) | MCG_C1_FRDIV(0b011) | MCG_C1_IREFS(0);

	/* Check that changes went through*/
	while(!((MCG->S & MCG_S_OSCINIT0_MASK) == MCG_S_OSCINIT0(1))){}
	while(!((MCG->S & MCG_S_IREFST_MASK) == 0)){}
	while(!((MCG->S & MCG_S_CLKST_MASK) == MCG_S_CLKST(0b10))){}


	/* Transition: FBE -> PBE
	 * Switch to PLL from FLL
	 *
	 * The following options are set:
	 * Pre-divider PRDIV0 = 4 -> resulting in 2MHz input for PLL
	 * Multiplier VDIV0 = 30 -> resulting in 60MHz internal reference
	 * Set bit to use PLL: PLLS =1
	 */

	MCG->C5 = MCG_C5_PRDIV0(0b00011);                 // Divide by 4 -> 8MHz/4=2MHz
	MCG->C6 = MCG_C6_VDIV0(0b00110) | MCG_C6_PLLS(1); // Multiply by 30 -> 2MHz * 30=60MHz + set PLL

	 /*Check that changes went through*/
	 while(!((MCG->S & MCG_S_PLLST_MASK) == MCG_S_PLLST(0b1))){} //Wait until PLL is locked on
	 while(!((MCG->S & MCG_S_LOCK0_MASK) == MCG_S_LOCK0(0b1))){} //Wait until PLL is locked on


	 /* Transition: PBE -3-> PEE
	  * Get out of bypass mode and turn on clock source for PLL
	  */

	 MCG->C1 = MCG_C1_CLKS(0b00);

	 /*Check that changes went through*/
	 while(!((MCG->S & MCG_S_CLKST_MASK) == MCG_S_CLKST(0b11))){} //Wait until PLL is locked on

	 /* Now divide the internal reference clock in the SIM module
	  * to get the clock signals to the rest of the chip.
	  *
	  * The following options are set:
	  * OUTDIV1 is set to 0b11, which corresponds to divide by 4.
	  * OUTDIV4 is set to 0, which corresponds to divide by 1.
	  */
	 SIM->CLKDIV1= SIM_CLKDIV1_OUTDIV1(0b0011) | SIM_CLKDIV1_OUTDIV4(0); //60MHz/4 = 15MHz


	 /* Though this is likely redundant based on the wait flags, it is good practice
	  * to wait for a few clock cycles after changing the clock configuration to
	  * make sure everything has stabilized.
	  */
	 delay(1);
}


void delay(uint32_t ms){
	for(int i= ms; i>0; i--){

		/* Each clock cycles is 1/15MHz
		 * So per ms there are: 1*10^-3 * 15^10^6 / 3 = 5000
		 * loops through the small 3-clock cycle helper function. */
		 loop_3cycles(5000);
	}
}

void led_init_frdm(void){

	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

	//MUX to GPIO
	PORTE->PCR[29] = PORT_PCR_MUX(001);
	PORTD->PCR[5] =  PORT_PCR_MUX(001);

	//Set pin directions
	PTD->PDDR |= 1<<5;
	PTE->PDDR |= 1<<29;

	//Make sure LEDs are off
	PTD->PSOR = 1<<5;
	PTE->PSOR = 1<<29;

}

/*
 * Manipulate red LED pin
 */
void red_on_frdm(void){
	PTE->PCOR = 1<<29;
}
void red_off_frdm(void){
	PTE->PSOR = 1<<29;
}
void red_toggle_frdm(void){
	PTE->PTOR = 1<<29;
}

/*
 * Manipulate green LED pin
 */
void green_on_frdm(void){
	PTD->PCOR = 1<<5;
}
void green_off_frdm(void){
	PTD->PSOR = 1<<5;
}
void green_toggle_frdm(void){
	PTD->PTOR = 1<<5;
}

