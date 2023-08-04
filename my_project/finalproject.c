#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "switches.h"
#include "state_machineC.h"

/////////////
//switches.h  (where it used to be before i moved it)
////////////

short redrawScreen = 1;

int lvl = 1;

int x = 1;  // x and y cordinates of the worm (blue block) 
int y = 1;

////////////
//swtiches.c  (where it used to be before i moved it)
////////////

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

//////////////////
//state_machineC.c  (where it used to be before i moved it)
//////////////////

int song = 1;
int interrupts = 0;
int c = 0;

void wdt_c_handler(void)
{
  //////     SONG TEST  /////////
  if (song == 0) {       //      turn off songs
    buzzer_set_period(0);
  }
  if (song == 1) {  // song for lvls 
    interrupts++;

    int notes[16] = {1803,1351,1203,1136,1803,1351,1203,1136,1702,1351,1203,1702,1351,1203,1136,0};
    int n = 16;

    buzzer_set_period(notes[c]);
    
    if (interrupts >= 250) {
      interrupts = 0;
      c++;
    }
    if(c == 16)
      c = 0;
  }
  if (song == 2) {  // song for end screen
    interrupts++;  

    int notes[8] = {6067,5405,4819,4545,4049,3607,3214,3033};
    int n = 8;

    buzzer_set_period(notes[c]);
    
    if (interrupts >= 30) {
      interrupts = 0;
      c++;
    }
    if(c == 8)
      c = 0;
  }
  /////////////////////////////////

  if (sw1) {  //  up switch
    y -= 1;  
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  }
  if (sw2) { // left switch
    x -= 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  } 
  if(sw3) {  // right switch 
    x += 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  }
  if (sw4) {  // down switch
    y += 1;
    fillRectangle(x, y, 15, 15, COLOR_BLUE);
  }
  //                            LVL 1 LIMITS
  
  if (((x+7) >= 22) & ((y+7) <= 31) & (lvl == 1)) {
    lvl = 1;
    buzzer_set_period(500);
    update();   // top lava for lvl 1
  }
  if (((x+7) >= 22) & ((x+7) <= 48) & ((y+7) <= 97) & (lvl == 1)) {
    lvl = 1;
    buzzer_set_period(500);
    update();  // middle left lava for lvl 1
  }
  if (((x+7) >= 22) & ((x+7) <= 96) & ((y+7) >= 97) & ((y+7) <= 112) & (lvl == 1)) {
    lvl = 1;
    buzzer_set_period(500);
    update();  // middle lava for lvl 1
  }
  if (((x+7) >= 81) & ((x+7) <= 96) & ((y+7) >= 65) & ((y+7) <= 97) & (lvl == 1)) {
    lvl = 1;
    buzzer_set_period(500);
    update();   // middle left lava for lvl 1 
  }
  if (((y+7) >= 145) & (lvl == 1)) {
    lvl = 1;
    buzzer_set_period(500);
    update();   // bottom lava for lvl 1 
  }
  if (((x+7) >= 49) & ((x+7) <= 80) & ((y+7) >= 81) & ((y+7) <= 96) & (lvl == 1)) {
    lvl = 2;
    buzzer_set_period(5000);
    update();   // goal for lvl 1
  }
  
  //                             LVL 2 LIMITS
  
  if (((x+7) <= 15) & ((y+7) >= 22) & (lvl == 2)) {
    lvl = 2;
    buzzer_set_period(500);
    update();   // left lava for lvl 2
  }
  if (((x+7) >= 113) & (lvl == 2)) {
    lvl = 2;
    buzzer_set_period(500);
    update();  // right lava for lvl 2
  }
  if (((x+7) >= 15) & ((x+7) <= 78) & ((y+7) >= 17) & ((y+7) <= 32) & (lvl == 2)) {
    lvl = 2;
    buzzer_set_period(500);
    update();  // top lava for lvl 2
  }
  if (((x+7) >= 49) & ((x+7) <= 114) & ((y+7) >= 65) & ((y+7) <= 80) & (lvl == 2)) {
    lvl = 2;
    buzzer_set_period(500);
    update();   // middle lava for lvl 2 
  }
  if (((x+7) >= 15) & ((x+7) <= 78) & ((y+7) >= 113) & ((y+7) <= 128) & (lvl == 2)) {
    lvl = 2;
    buzzer_set_period(500);
    update();   // bottom lava for lvl 2 
  }
  if (((x+7) >= 17) & ((x+7) <= 32) & ((y+7) >= 129) & ((y+7) <= 160) & (lvl == 2)) {
    lvl = 3;
    buzzer_set_period(5000);
    update();   // goal for lvl 2
  }
  if(song == 1 & lvl == 3) {
    song = 2;
    interrupts = 0;  //      song change for endscreen
    c = 0;
  }
  
  //                         END SCREEN LIMITS
  if (((x+7) >= 81) & ((x+7) <= 96) & ((y+7) >= 97) & ((y+7) <= 112) & (lvl == 3)) {
    lvl = 1;
    buzzer_set_period(500);
    update();   // lava for end screen 
  }

  if (song == 2 & lvl == 1)
    song = 1;             // song change for lvls


  //                      BOUNDARIES FOR THE SCREEN
  
  if ((((x+7) < 0) | ((x+7)  > 128) | ((y+7) < 0) | ((y+7) > 160)) & (lvl == 1)) {
    lvl = 1;
    buzzer_set_period(500);
    update();  // boundaries for lvl 1
  }
  if ((((x+7) < 0) | ((x+7)  > 128) | ((y+7) < 0) | ((y+7) > 160)) & (lvl == 2)) {
    lvl = 2;
    buzzer_set_period(500);
    update();  // boundaries for lvl 2
  }
  if ((((x+7) < 0) | ((x+7)  > 128) | ((y+7) < 0) | ((y+7) > 160)) & (lvl == 3)) {
    lvl = 3;
    buzzer_set_period(500);
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

//////////////////////
//p2_interrupt_handler (where it used to be before i moved it)
//////////////////////
