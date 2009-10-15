#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "gravity.h"

class Player;

class Game {
	public:
	Game();
	void update();
	void show();
	void mainLoop();
	Player *player;
	GravityManager *gravityManager;
};

#endif
