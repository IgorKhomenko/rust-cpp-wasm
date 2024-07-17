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

extern "C"
{
  Add *Add_C_new(int x, int y)
  {
    return new Add(x, y);
  }

  void Add_C_delete(Add *add)
  {
    delete add;
  }

  int Add_C_getSum(Add *add)
  {
    return add->getSum();
  }
}