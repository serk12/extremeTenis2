#include <stdio.h>
#include <string.h>
#include <tonc.h>
#include "all_gfx.h"
#include "back.h"
#include "play.h"
#include "enemy.h"
#include "shot.h"
#include "credit.h"

static int seed, mode, actualMode; //0 animation //1 game

void calcColisions() {
	for (int i = 0; i < _qttyShots; ++i) {
		int sizeX = 16;
		int sizeY = 22;
		int distX = (_shots[i][0]- _offsetX) - SCREENPOSX;
		int distY = (_shots[i][1]- _offsetY) - SCREENPOSY;
		if (distX > 0 && distX < sizeX && distY > 0 && distY < sizeY) mode = 0; //coment for easy mode
		for (int j = 0; j < _qttyEnemy; ++j) {
			if (_enemy[j][0] != -1 && _enemy[j][1] != -1) {
				distX = _shots[i][0] - _enemy[j][0];
				distY = _shots[i][1] - _enemy[j][1];
				if (distX >= 0 && distX <= sizeX && distY >= 0 && distY <= sizeY) {
				  _enemy[j][0] = _enemy[j][1] = -1;
					--_qttyEnemyLive;
					obj_hide(&oam_mem[OFFSETMEME + j]);
					if (_qttyEnemyLive == 0 && _qttyEnemy == 32) mode = 0;
				}
			}
		}
	}
}

void changeMode() {
	if (mode != actualMode) {
		if (mode == 1) {
			REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
			playerInit();
			backgroundInit();
			enemyInit();
			shotInit();
		}
		else if (mode == 0){
			REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
			initCredit();
		}
		actualMode = mode;
	}
}

void init_game() {
	irq_init(NULL);
	irq_add(II_VBLANK,NULL);
	seed = mode = 0;
	actualMode = 1;
}

void update() {
	++seed;
	if (mode == 1) {
		playerUpdate();
		enemyUpdate(seed);
		shotsUpdate();
	}
	else {
		creditUpdate();
	}
}

void event() {
	key_poll();
	if (mode == 1) {
	playerEvent();
	if (key_hit(KEY_A))
		createNewShot(SCREENPOSX + _offsetX, SCREENPOSY + _offsetY);
	}
	else {
		if (key_hit(KEY_START)) {
			mode = 1;
			actualMode = 0;
		}
	}
}

void draw() {
	if (mode == 1) {
		playerPrint();
		backgroundPrint();
		int posWorld[2] = {_offsetX, _offsetY};
		enemyPrint(posWorld);
		shotsPrint(posWorld);
		calcColisions();
	}
	else {
		drawCredit();
	}
}

int main() {
	init_game();
	while (1) {
		VBlankIntrWait();
		event();
		update();
		changeMode();
		draw();
	}
}
