#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

short redrawScreen = 1;

int lvl = 1;

int x = 1;  // x and y cordinates of the worm (blue block) 
int y = 1;

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

int switches = 0;

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


void lvl1()
{
  clearScreen(COLOR_GREEN);
  
  fillRectangle(1, 1, 15, 15, COLOR_BLUE);    //start of worm
  fillRectangle(49, 81, 31, 15, COLOR_GRAY); //end hole

  fillRectangle(22, 0, 106, 31, COLOR_RED); //top horizontal lava
  fillRectangle(22, 31, 26, 66, COLOR_RED); //top vertical lava
  fillRectangle(22, 97, 74, 15, COLOR_RED); //middle horizontal lava
  fillRectangle(81, 65, 15, 32, COLOR_RED); //middle vertical lava
  fillRectangle(0, 145, 128, 15, COLOR_RED); // bottom lava
}


void lvl2()
{
  clearScreen(COLOR_GREEN);
  
  fillRectangle(1, 1, 15, 15, COLOR_BLUE);    //start of worm
  fillRectangle(17, 129, 15, 31, COLOR_GRAY); //end hole

  fillRectangle(0, 22, 15, 139, COLOR_RED); //left vertical lava
  fillRectangle(113, 0, 16, 160, COLOR_RED); //right vertical lava
  fillRectangle(15, 22, 63, 10, COLOR_RED); //top horizontal lava
  fillRectangle(49, 65, 65, 15, COLOR_RED); //middle horizontal lava
  fillRectangle(15, 113, 63, 15, COLOR_RED); //bottom horizontal lava
}

/*
void lvl3()                      //TEST LEVEL//
{
  clearScreen(COLOR_GREEN);
  
  fillRectangle(1, 1, 15, 15, COLOR_BLUE);    //start of worm
  fillRectangle(1, 65, 31, 15, COLOR_GRAY); //end hole

  fillRectangle(17, 0, 31, 15, COLOR_RED); //top horizontal lava
  fillRectangle(81, 33, 15, 95, COLOR_RED); //right vertical lava
  fillRectangle(0, 49, 81, 15, COLOR_RED); //middle top horizontal lava
  fillRectangle(33, 64, 48, 31, COLOR_RED); //middle horizontal lava
  fillRectangle(33, 95, 15, 15, COLOR_RED); //middle bottom block lava
  fillRectangle(0, 145, 63, 15, COLOR_RED); //bottom horizontal lava
}
*/

void endScreen()
{
  clearScreen(COLOR_GREEN);

  drawString5x7(40,20, "YOU WON!!!", COLOR_BLACK, COLOR_GREEN);
  drawString5x7(25,40, "ENTER THE LAVA", COLOR_BLACK, COLOR_GREEN);
  drawString5x7(25,50, "TO PLAY AGAIN.", COLOR_BLACK, COLOR_GREEN);

  fillRectangle(33, 97, 15, 15, COLOR_BLUE);    //start of worm
  fillRectangle(81, 97, 15, 15, COLOR_RED);     // lava
}

void update()
{ 
  if(1) {
    switch (lvl) {
    case 1:
      x = 1;
      y = 1;
      lvl1();
      break;
    case 2:
      x = 1;
      y = 1;
      lvl2();
      break;
    case 3:
      x = 33;
      y = 97;
      endScreen();
      break;
    default:
      x = 1;
      y = 1;
      lvl1();
      break;
    }
  }
}

int interrupts = 0;
int i = 1;
int cycles= 8000;

void wdt_c_handler(void)
{
  //////     SONG TEST  /////////
  interrupts++;

  if (interrupts == (i*10))
    {
      i++;
      buzzer_set_period(cycles);
      cycles -= 200;
    }
  else if(cycles == 2000)
    {
      interrupts = 0;
      cycles = 8000;
      i = 1;
    }
  /////////////////////////////////

  if (sw1) {
    y -= 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  }
  if (sw2) {
    x -= 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  } 
  if(sw3) {
    x += 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  }
  if (sw4) {
    y += 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  }
  //                            LVL 1 LIMITS
  
  if (((x+7) >= 22) & ((y+7) <= 31) & (lvl == 1)) {
    lvl = 1;
    update();   // top lava for lvl 1
  }
  if (((x+7) >= 22) & ((x+7) <= 48) & ((y+7) <= 97) & (lvl == 1)) {
    lvl = 1;
    update();  // middle left lava for lvl 1
  }
  if (((x+7) >= 22) & ((x+7) <= 96) & ((y+7) >= 97) & ((y+7) <= 112) & (lvl == 1)) {
    lvl = 1;
    update();  // middle lava for lvl 1
  }
  if (((x+7) >= 81) & ((x+7) <= 96) & ((y+7) >= 65) & ((y+7) <= 97) & (lvl == 1)) {
    lvl = 1;
    update();   // middle left lava for lvl 1 
  }
  if (((y+7) >= 145) & (lvl == 1)) {
    lvl = 1;
    update();   // bottom lava for lvl 1 
  }
  if (((x+7) >= 49) & ((x+7) <= 80) & ((y+7) >= 81) & ((y+7) <= 96) & (lvl == 1)) {
    lvl = 2;
    update();   // goal for lvl 1
  }
  
  //                             LVL 2 LIMITS
  
  if (((x+7) <= 15) & ((y+7) >= 22) & (lvl == 2)) {
    lvl = 2;
    update();   // left lava for lvl 2
  }
  if (((x+7) >= 113) & (lvl == 2)) {
    lvl = 2;
    update();  // right lava for lvl 2
  }
  if (((x+7) >= 15) & ((x+7) <= 78) & ((y+7) >= 17) & ((y+7) <= 32) & (lvl == 2)) {
    lvl = 2;
    update();  // top lava for lvl 2
  }
  if (((x+7) >= 49) & ((x+7) <= 114) & ((y+7) >= 65) & ((y+7) <= 80) & (lvl == 2)) {
    lvl = 2;
    update();   // middle lava for lvl 2 
  }
  if (((x+7) >= 15) & ((x+7) <= 78) & ((y+7) >= 113) & ((y+7) <= 128) & (lvl == 2)) {
    lvl = 2;
    update();   // bottom lava for lvl 2 
  }
  if (((x+7) >= 17) & ((x+7) <= 32) & ((y+7) >= 129) & ((y+7) <= 160) & (lvl == 2)) {
    lvl = 3;
    update();   // goal for lvl 2
  }
  
  //                         END SCREEN LIMITS
  if (((x+7) >= 81) & ((x+7) <= 96) & ((y+7) >= 97) & ((y+7) <= 112) & (lvl == 3)) {
    lvl = 1;
    update();   // lava for end screen 
  }


  //                      BOUNDARIES FOR THE SCREEN
  
  if ((((x+7) < 0) | ((x+7)  > 128) | ((y+7) < 0) | ((y+7) > 160)) & (lvl == 1)) {
    lvl = 1;
    update();  // boundaries for lvl 1
  }
  if ((((x+7) < 0) | ((x+7)  > 128) | ((y+7) < 0) | ((y+7) > 160)) & (lvl == 2)) {
    lvl = 2;
    update();  // boundaries for lvl 2
  }
  if ((((x+7) < 0) | ((x+7)  > 128) | ((y+7) < 0) | ((y+7) > 160)) & (lvl == 3)) {
    lvl = 3;
    update();  // boundaries for end screen
  }
}


void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  while(1) {
    if(redrawScreen) {
      redrawScreen = 0;
      update();
    }    
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}



void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
