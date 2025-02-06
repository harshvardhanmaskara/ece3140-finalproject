/*
 * ECE3140Lab2.h
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

#ifndef ECE3140LAB2_H_
#define ECE3140LAB2_H_

#include <stdint.h> //Defines standard C-style int types

/*
 * This function sets the core and bus clocks to 15MHz
 * Only call this function once since it assumes the
 * default clock configuration for the board after a reset.
 */
void set15MHz(void);

/*
 * Handy delay function that you are welcome to use.
 * These functions assume a core clock of 15MHz.
 *
 *    delay(num) uses the loop_3delay function to block for num milliseconds
 *
 */
void loop_3cycles(int); //implemented in .s file
void delay(uint32_t ms);

/*
 * Sets up the pins and for GPIO to the two LEDs that are on the FRDM KL46z.
 *
 * You can use them for Part 3 and Part 4.
 */

void led_init_frdm(void);

void red_on_frdm(void);
void red_off_frdm(void);
void red_toggle_frdm(void);

void green_on_frdm(void);
void green_off_frdm(void);
void green_toggle_frdm(void);

#endif /* ECE3140LAB2_H_ */
