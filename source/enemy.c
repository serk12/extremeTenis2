#include "enemy.h"

void creatNewEnemys() {
  _qttyEnemyLive = _qttyEnemy;
  for (int i = 0; i < _qttyEnemy; ++i) {
    _enemy[i][0] = CENTER[0];
    _enemy[i][1] = CENTER[1];
    _enemy[i][2] = 0;
    obj_set_attr(&oam_mem[OFFSETMEME + i],ATTR0_TALL | ATTR0_8BPP,
                          ATTR1_SIZE_32, OFFSETSTITLE);
  }
}

void enemyInit() {
  _qttyEnemy = _timeMove = _count = _qttyEnemyLive = 0;
}
void enemyUpdate(int seed) {
  for (int i = 0; i < _qttyEnemy; ++i) {
    if (_enemy[i][0] != -1 && _enemy[i][1] != -1) {
      if (_timeMove > ((seed*(i+1)%6)+1)*10) {
        _enemy[i][2] = (seed*(i + 1) + _enemy[i][2])%4;
        _timeMove = 0;
      }
      else if (_enemy[i][0] > 224 || _enemy[i][0] < 144 || _enemy[i][1] > 224 || _enemy[i][1] < 24) {
        if (_enemy[i][0] > 224)
          _enemy[i][0] -= VELE;
        else if (_enemy[i][0] < 144)
          _enemy[i][0] += VELE;
        else if (_enemy[i][1] > 224)
          _enemy[i][1] -= VELE;
        else if (_enemy[i][1] < 144)
          _enemy[i][1] += VELE;
        _enemy[i][2] = (_enemy[i][2] + 1)%4;
        _timeMove = 0;
      }
      else {
        int dir = _enemy[i][2];
        switch (dir) {
          case 0:
          _enemy[i][0] -= VELE;
          break;
        case 1:
          _enemy[i][0] += VELE;
          break;
        case 2:
          _enemy[i][1] -= VELE;
          break;
        case 3:
          _enemy[i][1] += VELE;
          break;
        }
        int mov = dir%2;
        obj_set_attr(&oam_mem[OFFSETMEME + i],ATTR0_TALL | ATTR0_8BPP,
                              ATTR1_SIZE_32, OFFSETSTITLE + (mov*2 + _count%2)*16);
        _count = (_count + 1)%2;
        ++_timeMove;
      }
    }
  }
}

void enemyPrint(int posWorld[2]) {
  for (int i = 0; i < _qttyEnemy; ++i) {
    if (_enemy[i][0] != -1 && _enemy[i][1] != -1)
    obj_set_pos(&oam_mem[OFFSETMEME + i], _enemy[i][0] - posWorld[0],
                                          _enemy[i][1] - posWorld[1]);
  }
  if (_qttyEnemyLive == 0) {
    _qttyEnemy = (_qttyEnemy+1)%32;
    creatNewEnemys();
  }
}
