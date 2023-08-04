#include "state_machineC.h"

void update()
{
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
  }
}
