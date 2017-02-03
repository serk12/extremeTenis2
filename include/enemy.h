#ifndef ENEMY_H
#define ENEMY_H
#include <stdio.h>
#include <tonc.h>
#include <string.h>
#include "all_gfx.h"
  static const int OFFSETSTITLE = 64*3, OFFSETMEME = 1, VELE = 1,
                   CENTER[2] = {185, 117};
  int _qttyEnemy, _qttyEnemyLive, _count, _timeMove;
  int _enemy[32][3]; //X, Y, DIR//pos {-1,-1} === DEATH

  void enemyInit();
  void enemyUpdate(int seed);
  void enemyPrint(int posWorld[2]);
#endif
