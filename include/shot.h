#ifndef SHOT_H
#define SHOT_H
#include <stdio.h>
#include <tonc.h>
#include <string.h>
#include "all_gfx.h"

  int _qttyShots, _lastShotId;
  static const int  OFFSETTITLEB = 64*2, OFFSETMEM = 32, SIZEB = 16, VEL = 2,
                    MAXSHOTS = 16;
                           //UP:0 Mid:1 Down:2 / Right:0 Left:1
  //0 == X //// 1 == Y == //// 2 == angle Y /// 3 == angle X
  int _shots[16][4];


  void shotInit();
  void createNewShot(int posX, int posY);
  void shotsUpdate();
  void shotsPrint(int offset[2]);
#endif
