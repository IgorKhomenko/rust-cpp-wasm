#ifndef A2DD2_H
#define A2DD2_H

class A2DD2
{
  int gx;
  int gy;

public:
  A2DD2(int x, int y) {
    gx = x;
    gy = y;
  }
  int getSum() {
    return gx + gy;
  }
};

#endif