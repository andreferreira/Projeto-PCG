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
		void loadMap();
	public:
		Ponto camera;
		Game();
		void mainLoop();
		void desenhaMira(Ponto aim);
		Player *player;
		Mapa *mapa;
		void addPlatform(Platform* plat);
		GravityManager *gravityManager;
};

#endif
