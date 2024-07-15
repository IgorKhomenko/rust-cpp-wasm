// A2DD.h
#ifndef A2DD_H
#define A2DD_H

class A2DD
{
  int gx;
  int gy;

public:
  A2DD(int x, int y);
  int getSum();
};

#endif

A2DD::A2DD(int x, int y)
{
  gx = x;
  gy = y;
}

int A2DD::getSum()
{
  return gx + gy;
}