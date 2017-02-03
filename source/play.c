#include "play.h"

bool canMove() {
  int type = TileLayer1[0][0][((_offsetY + SCREENPOSY + key_tri_vert()*VELY)/8)%32]
                             [((_offsetX + SCREENPOSX + key_tri_horz()*VELX)/8)%32];
  int type2= TileLayer1[0][0][((_offsetY + SCREENPOSY + key_tri_vert()*VELY + SPRITESIZEY)/8)%32]
                             [((_offsetX + SCREENPOSX + key_tri_horz()*VELX + SPRITESIZEX)/8)%32];
  return (BLOCKMOVE < type) && (BLOCKMOVE < type2);
}

void playerInit() {
  memcpy(&tile8_mem[4][0], playerTiles,playerTilesLen);
  memcpy(pal_obj_mem,playerPal,playerPalLen);
  oam_init(oam_mem,128);
  obj_set_attr(&oam_mem[0],ATTR0_TALL | ATTR0_8BPP,ATTR1_SIZE_32, 0);
  // obj_set_pos(&oam_mem[0], SCREENPOSX, SCREENPOSY);
  _state = _pose = _delta = 0;
  REG_BG0VOFS = REG_BG0HOFS = _offsetX = _offsetY = 0;
  _moving = false;
}

void playerUpdate() {
  if (_moving) {
    if (_delta > 5) {
      _state = (_state + 16)%(16*4);
      _delta = 0;
    }
    else ++_delta;
  }
}

void playerEvent() {
  _moving = key_is_down(KEY_DOWN | KEY_UP | KEY_LEFT | KEY_RIGHT);
  if (_moving) {
    if (canMove()) {
      _offsetX = (_offsetX + key_tri_horz()*VELX)%(32*8);
      _offsetY = (_offsetY + key_tri_vert()*VELY)%(32*8);
      REG_BG0VOFS = _offsetY;
      REG_BG0HOFS = _offsetX;
    }
  }

  if (key_is_down(KEY_UP)) _pose = 16*4;
  else if (key_is_down(KEY_DOWN)) _pose = 0;
}
void playerPrint() {
    int tile = _pose + _state;
  	obj_set_attr(&oam_mem[0],ATTR0_TALL|ATTR0_8BPP,ATTR1_SIZE_32,ATTR2_PALBANK(0) | tile);
  	obj_set_pos(&oam_mem[0], SCREENPOSX, SCREENPOSY);
}
