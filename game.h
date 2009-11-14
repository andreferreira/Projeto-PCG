#ifndef GAME_H
#define GAME_H

#include <string>
#include "gravity.h"
#include "mapa.h"
#include "weaponmanager.h"
#include "configmanager.h"

class Player;
class Mapa;

class Game {
	private:
		void show();
		void loadMap(std::string mapname);
		std::string currentMap;
		WeaponManager* weaponManager;
		ConfigManager *config;
	public:
		Ponto camera;
		Game(ConfigManager *cfg);
		void mainLoop();
		void desenhaMira(Ponto aim);
		Player *player;
		Mapa *mapa;
		void addPlatform(Platform* plat);
		GravityManager *gravityManager;
		void reloadLua();
		void removePlatforms();
};

#endif
