#ifndef PLAYER_H
#define PLAYER_H
#include <tonc.h>
#include <string.h>
#include "map.h"
#include "all_gfx.h"
  static const int SCREENPOSX = 50, SCREENPOSY = 70, SPRITESIZEX = 16, SPRITESIZEY = 21, VELX = 2, VELY = 2;
  static const int BLOCKMOVE = 8*4 - 1;
  int _state, _pose, _delta, _offsetY, _offsetX;
  bool _moving;
  void playerInit();
  void playerUpdate();
  void playerEvent();
  void playerPrint();
  bool canMove();
#endif
