#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "gravity.h"
#include "mapa.h"

class Player;

class Mapa;

class Game {
	private:
		void show();
		void geraMapa();
	public:
		Game();
		void mainLoop();
		Player *player;
		Mapa *mapa;
		GravityManager *gravityManager;
};

#endif
