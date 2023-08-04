#include <msp430.h>

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1 
#define SW2 2 
#define SW3 4 
#define SW4 8

#define SWITCHES 15

extern int switches;
extern char sw1;
extern char sw2;
extern char sw3;
extern char sw4;

// initializes the switches
void switch_init(void);

//  handles switch interrupts
void switch_interrupt_handler();
