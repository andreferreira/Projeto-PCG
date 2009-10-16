#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "gravity.h"
#include <vector>

class Player;

class Game {
	public:
	std::vector<Linha> mapa;
	Game();
	void update();
	void show();
	void mainLoop();
	void geraMapa();
	Player *player;
	GravityManager *gravityManager;
};

#endif
