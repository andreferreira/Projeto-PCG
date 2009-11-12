#ifndef GAME_H
#define GAME_H

#include "gravity.h"
#include "mapa.h"
#include <string>

class Player;
class Mapa;

class Game {
	private:
		void show();
		void loadMap(std::string mapname);
		std::string currentMap;
	public:
		Ponto camera;
		Game();
		void mainLoop();
		void desenhaMira(Ponto aim);
		Player *player;
		Mapa *mapa;
		void addPlatform(Platform* plat);
		GravityManager *gravityManager;
		void reloadMap();
		void removePlatforms();
};

#endif
