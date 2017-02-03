#include "credit.h"

void initCredit() {
  base = openingBitmap; // <- waring POS OK
  current = base;
  limit = base + (openingBitmapLen /4) - (240*160/2);
  memcpy16(vid_mem, current, 240*160);
  x = stop = 0;
}

void creditUpdate() {
  ++frame;
  if (frame > 5 && stop == 0) {
    current += 240*160/2;
    frame = 0;
  }
}

void drawCredit() {
  if (current > limit) {
    stop = 1;
    current -= 240*160/2;
  }
	memcpy16(vid_mem, current, 240*160);
}
