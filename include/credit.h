#ifndef CREDIT_H
#define CREDIT_H
#include <stdio.h>
#include <tonc.h>
#include <string.h>
#include "all_gfx.h"

  static const int NUMFRAMES = 45;
  int* base;
  int* limit;
  int* current;
  int frame, x, stop;
  void initCredit();
  void creditUpdate();
  void drawCredit();

#endif
