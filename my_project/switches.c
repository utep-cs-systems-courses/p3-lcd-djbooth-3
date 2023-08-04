#include "switches.h"

int switches = 0; 

char sw1 = 0;
char sw2 = 0;
char sw3 = 0;
char sw4 = 0;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
  sw1 = (p2val & SW1)? 0 : 1;
  sw2 = (p2val & SW2)? 0 : 1;
  sw3 = (p2val & SW3)? 0 : 1;
  sw4 = (p2val & SW4)? 0 : 1; 
}
