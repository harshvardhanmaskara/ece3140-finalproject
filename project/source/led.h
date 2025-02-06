/* 
 * led.h
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

#ifndef LED_H_
#define LED_H_

#include <stdint.h> //include for int types

/* Struct for passing in RGB settings for LED1 and LED2
 *
 * This is a common practice in C, where we want to be able to group
 * logically related data together and control how its binary representation
 * will look. Here, we pack three 8-bit values into 32 bits and name them
 * so we can manipulate them, see test_part2.c.Each 8-bit value is an
 * unsigned int, and c defines standard types for us.
 *
 * "uint8_t" stands for: Unsigned INT, 8-bit wide, Type so uint8_t.
 *
 * The lowest order byte is blue, then red, then green. The filler
 * variable ensures the struct lines up to a 32-bit boundary.
 *
 * This means we can pass in a single argument of type gbr32_t as
 * a function argument and it will fit neatly into R0 with the bits
 * we need to output in the correct order.
 *
 * Note the order of the colors to correspond to the layout of the
 * WS2812 communication protocol.
 */
typedef struct _grb32 {
	uint8_t blue;
	uint8_t red;
	uint8_t green;
	uint8_t __filler;
} grb32_t;


/**************************************
 * This set up all the pins on the FRDMKL46z board so you can use the LEDs.
 *
 * Once the function returns ALL the LEDs on the Lab 2 board should should be
 * turned off, and the serial pin connected to LED1 should be low. Use
 * other functions of the library to achieve this.
 *
 * Typically you would  expect this function to be called once in the
 * beginning, but calling it multiple times should work too.
 *
 * Implement this function in led.c
 **************************************/
void led_init(void);



/**************************************
 * Functions for LED 0
 *
 * These should be implemented in led.c and relate to Part 1 of the lab.
 *
 * Look at test_part1.c for usage examples.
 **************************************/


/* The functions below should turn on, turn off or toggle the appropriate
 * component LED in LED0. They should have no other side effects.
 *
 * Implement these function in led.c
 */
void red_on(void);
void red_off(void);
void red_toggle(void);

void blue_on(void);
void blue_off(void);
void blue_toggle(void);

void green_on(void);
void green_off(void);
void green_toggle(void);


/* Turn the red,green,and blue LED of LED0 off
 *
 * Implement these functions in led.c
 */
void all_leds_off(void);


/**************************************
 * Functions for interacting with the serial LEDs (LED1 and LED2)
 *
 * Both LED1 and LED2 are of type WS2812B-ver5 and are controlled from a
 * single pin on the board. These functions relate to Part 2 of the lab
 * and should be implemented in led.s and led.c.
 *
 * Look at test_part2.c for usage examples.
 **************************************/


/* The function should generate a series of 24 pulses that indicate
 * zeros and ones for the power settings of the red, green, and blue
 * LEDs that are inside LEDs 1 and 2. The values that are output on
 * the pin should be taken from the input argument. The dummy variable
 * should be ignored.
 *
 * There are tight timing requirements that are difficult/impossible
 * There to achieve in C. Implement this function in led.s
 */
void set_led(grb32_t rgb_val);


/* Output a bitstream to turn off a serial LED by setting the power for the
 * red, green, and blue LEDs to zero.
 *
 * Implement this function in led.c
 */
void led_off(void);


/* This function should take an array of length num_led of gbr32_t values
 * and sequentially output them on the appropriate pin to control num_led
 * daisy-chained LEDs. rgb_vals[0] should be output first. Calling this
 * function twice in a row should overwrite the old values of the LEDs.
 *
 * Since the board only has two chained LEDs, you should only see the first
 * two RGB values displayed on the board even if you call it with more.
 *
 * Implement this function in led.c
 */
void set_leds(grb32_t * rgb_vals, uint32_t num_led);


/* Output a bitstream for turning off num_led daisy-chained LEDs
 *
 * Implement this function in led.c
 */
void leds_off(uint32_t num_led);



/*
 * This function should add the color setting capability of the serial LEDs
 * to your RGB led by setting the power output in software. You should be able
 * to use led0_out(gbr_t) exactly the same as set_led, except that it should
 * set LED0 instead of a serial LED.
 *
 * If you choose to do the extra credit, implement this function in ledEC.c
 */
void set_led0(grb32_t rgb_val);

#endif /* LED_H_ */
