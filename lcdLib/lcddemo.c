/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

int max(int a, int b) {return a > b ? a : b; }
int min(int a, int b) {return a > b ? b : a; }


/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  //drawHorizontalHourGlass(screenWidth >> 1, screenHeight >> 1, 15, COLOR_WHITE);
  void drwaHorizontalHourGlass(int controlCol, int controlRow, int size, int color)
  {
    int c = 0;
    int r = 0;

    for (int j = 0; j < size; j++)
      {
	int upper = min(-r, +r);
	int lower = max(-r, +r);
	int drawCol = c;
	for (int i = upper; i <= lower; i++)
	  {
	    drawPixel(controlCol+drawCol, controlRow+i, color);
	    drawPixel(controlCol-drawCol, controlRow+i, color);
	  }
	c += 1;
	r += 1;
      }
  }

  /* horizontal Hour glass outline

  int c = 0;
  int r = 0;
  for (int j = 0; j < 30; j++)
    {
      int upper = (screenHeight >> 1)-r;
      int lower = (screenHeight >> 1)+r;
      drawPixel((screenWidth >> 1)+c, upper, COLOR_WHITE);
      drawPixel((screenWidth >> 1)+c, lower, COLOR_WHITE);

      drawPixel((screenWidth >> 1)-c, upper, COLOR_WHITE);
      drawPixel((screenWidth >> 1)-c, lower, COLOR_WHITE);

      if (c == 29)
	{
	  for (int i = upper; i < lower; i++)
	    {
	      drawPixel((screenWidth >> 1)+c, i, COLOR_WHITE);
	      drawPixel((screenWidth >> 1)-c, i, COLOR_WHITE);
	    }
	}
      
      c += 1;
      r += 1;
    }
  */

  // vertical hour glass
  
  
  /* square outline

  int c = 0;
  int r = 0;

  for (int j = 0; j < 30; j++)
    {
      drawPixel(40+c, 60, COLOR_WHITE);
      drawPixel(40+c, 90, COLOR_WHITE);
      drawPixel(40, 60+r, COLOR_WHITE);
      drawPixel(70, 60+r, COLOR_WHITE);

      c += 1;
      r += 1;
    }
  */
  
  /* square filled

  int c = 0;
  int r = 0;
  for (int j = 0; j < 30; j++)
    {
      int upper = 60;
      int lower = 90;
      for (int i = upper; i <= lower; i++)
	{
	  drawPixel(40+c, i, COLOR_WHITE);
	}
      c += 1;
    }
  */

  /* diamond outline

  int c = 0;
  int r = 0;
  for (int j = 0; j < 30; j++)
    {
      drawPixel(30+c, 70+r, COLOR_WHITE);
      drawPixel(30+c, 70-r, COLOR_WHITE);
      drawPixel(90-c, 70+r, COLOR_WHITE);
      drawPixel(90-c, 70-r, COLOR_WHITE);

      c += 1;
      r += 2;
    }
  */

  /* diamond filled

  int c = 0;
  int r = 0;
  for (int j = 0; j < 30; j++)
    {
      int upper = 70-r;
      int lower = 70+r;
      for (int i = upper; i <= lower; i++)
	{
	  drawPixel(30+c, i, COLOR_WHITE);
	  drawPixel(88-c, i, COLOR_WHITE);
	}
      c += 1;
      r += 2;
    }
  */

  /* octagon outline

  int c = 0;
  int r = 0;
  for (int j = 0; j < 25; j++)
    {
      // left and right sides
      drawPixel(30, 70+r, COLOR_WHITE);
      drawPixel(100, 70+r, COLOR_WHITE);

      // top and bottom sides
      drawPixel(53+c, 49, COLOR_WHITE);
      drawPixel(53+c, 117, COLOR_WHITE);

      c += 1;
      r += 1;
    }

  c = 0;
  r = 0;
  
  for (int k = 0; k < 22; k++)
    {
      // left diagnols
      drawPixel(30+c, 70-r, COLOR_WHITE);
      drawPixel(30+c, 95+r, COLOR_WHITE);

      // right diagnols
      drawPixel(100-c, 70-r, COLOR_WHITE);
      drawPixel(100-c, 95+r, COLOR_WHITE);

      c += 1;
      r += 1;
    }
  */
  


  /* octagon filled

  int c = 0;
  int r = 0;
  for (int j = 0; j < 27; j++)
    {
      int upper = 49;
      int lower = 117;
      for (int i = upper; i < lower; i++)
	{
	  drawPixel(52+c, i, COLOR_WHITE);
	}
      c += 1;
    }

  c = 0;
  r = 0;
  for (int k = 0; k < 22; k++)
    {
      int upper = 70-r;
      int lower = 95+r;
      for (int z = upper; z < lower; z++)
	{
	  drawPixel(30+c, z, COLOR_WHITE);
	  drawPixel(100-c, z, COLOR_WHITE);
	}
      c += 1;
      r += 1;
    }
  */
}

