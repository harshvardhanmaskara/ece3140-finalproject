/*
 * led.c
 *
 *  Created on: Mar 02, 2024
 *      Author: hm475
 */

#include "led.h"
#include <MKL46Z4.h>

//LED0 (Digital)
void led_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //clock
	PORTE->PCR[16] |= PORT_PCR_MUX(0b001);//red
	PTE->PDDR |= GPIO_PDDR_PDD(1 << 16);//red
	PORTE->PCR[6] |= PORT_PCR_MUX(0b001);//green
	PTE->PDDR |= GPIO_PDDR_PDD(1 << 6);//green
	PORTE->PCR[2] |= PORT_PCR_MUX(0b001);//blue
	PTE->PDDR |= GPIO_PDDR_PDD(1 << 2);//blue

	PORTE -> PCR[3] = PORT_PCR_MUX(0b001);
	PTE -> PDDR |= GPIO_PDDR_PDD(1 << 3);

	PTE->PCOR |= (1 << 3);

	all_leds_off();
}
void red_on(void){
	PTE -> PCOR |= (1 << 16);
}
void red_off(void){
	PTE -> PSOR |= (1 << 16);
}
void red_toggle(void){
	PTE -> PTOR |= (1 << 16);
}
void blue_on(void){
	PTE -> PCOR |= (1 << 2);
}
void blue_off(void){
	PTE -> PSOR |= (1 << 2);
}
void blue_toggle(void){
	PTE -> PTOR |= (1 << 2);
}
void green_on(void){
	PTE -> PCOR |= (1 << 6);
}
void green_off(void){
	PTE -> PSOR |= (1 << 6);
}
void green_toggle(void){
	PTE -> PTOR |= (1 << 6);
}

void all_leds_off(void){
	red_off();
	green_off();
	blue_off();
}

//LED1 and LED2 (Serial)
void set_leds(grb32_t * rgb_vals, uint32_t num_led){
	for (int i=0; i<num_led; i=i+1){
		set_led(rgb_vals[i]);
	}
	delay(1);
}

void led_off(void){
	grb32_t off = {0,0,0};
	set_led(off);
}

void leds_off(uint32_t num_led) {
	for (int i=0; i<num_led; i=i+1){
		led_off();
	}
	delay(1);
}

