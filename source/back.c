#include "back.h"

void backgroundInit() {
  memcpy(&tile8_mem[0][0], backgroundTiles, backgroundTilesLen);
  memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
  memcpy(&se_mem[30][0], TileLayer1[0][0], 32*32*sizeof(SCR_ENTRY));

  REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
}

void backgroundPrint() {

}
