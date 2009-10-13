#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game {
	public:
	Game();
	void update();
	void show(Player &jogador);
	void mainLoop();
};

#endif
