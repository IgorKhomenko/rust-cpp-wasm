// add.h
#ifndef add_H
#define add_H

class Add
{
  int gx;
  int gy;

public:
  Add(int x, int y);
  int getSum();
};

// wrapper
extern "C"
{
  Add *Add_C_new(int x, int y);
  void Add_C_delete(Add *add);
  int Add_C_getSum(Add *add);
}

#endif