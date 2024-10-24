#include "add.h"

Add::Add(int x, int y)
{
  gx = x;
  gy = y;
}

int Add::getSum()
{
  return gx + gy;
}