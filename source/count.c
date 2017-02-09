#include "count.h"

void countInit(int maxEnemys) {
  for (int i = 0; i < maxEnemys; ++i) {
    obj_set_attr(&oam_mem[i + OFFSETALL],ATTR0_SQUARE | ATTR0_8BPP,ATTR1_SIZE_16, 64*3);
    obj_set_pos(&oam_mem[i + OFFSETALL],16*(i%15), (i/15)*16);
  }
  enemysLeft = (maxEnemys - 1);
}

void countDown() {
  obj_hide(&oam_mem[OFFSETALL + enemysLeft]);
  --enemysLeft;
}
