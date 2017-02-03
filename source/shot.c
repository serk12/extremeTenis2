#include "shot.h"

void shotInit() {
  _qttyShots = 0;
  _lastShotId = -1;
}

void createNewShot(int posX, int posY) {
  if (_qttyShots < MAXSHOTS) ++_qttyShots;
  _lastShotId = (_lastShotId + 1)%MAXSHOTS;
  _shots[_lastShotId][0] = posX + SIZEB;
  _shots[_lastShotId][1] = posY + SIZEB/2;
  int angle = 1;
  if (key_is_down(KEY_DOWN)) angle = 2;
  else if (key_is_down(KEY_UP)) angle = 0;
  _shots[_lastShotId][2] = angle;
  _shots[_lastShotId][3] = 0;
  obj_set_attr(&oam_mem[_lastShotId + OFFSETMEM], ATTR0_SQUARE |
                ATTR0_8BPP,ATTR1_SIZE_8, OFFSETTITLEB); //ToDO: priority draw
}
void shotsUpdate() {
  for (int i = 0; i < _qttyShots; ++i) {
    //calc bounce
    if (_shots[i][0] < 16 || _shots[i][0] >  232) {
      if (_shots[i][3] == 0)
        _shots[i][3] = 1;
      else
      _shots[i][3] = 0;
    }
    if (_shots[i][1] < 16 || _shots[i][1] > 232) {
      if (_shots[i][2] == 0)
        _shots[i][2] = 2;
      else if (_shots[i][2] == 2)
        _shots[i][2] = 0;
    }
    //calc next pos
    if (_shots[i][3] == 0)
      _shots[i][0] += VEL;
    else
      _shots[i][0] -= VEL;

    if (_shots[i][2] == 0)
      _shots[i][1] -= VEL;
    else if (_shots[i][2] == 2)
      _shots[i][1] += VEL;
  }
}
void shotsPrint(int posWorld[2]) {
  for (int i = 0; i < _qttyShots; ++i) {
    obj_set_pos(&oam_mem[i + OFFSETMEM], _shots[i][0] - posWorld[0],
                                 _shots[i][1] - posWorld[1]);
  }
}
