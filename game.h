#ifndef GAME_H
#define GAME_H

#include <string>
#include "gravity.h"
#include "mapa.h"
#include "weaponmanager.h"

class Player;
class Mapa;
class ShotManager;

class Game {
	private:
		void show();
		void loadMap(std::string mapname);
		std::string currentMap;
		WeaponManager* weaponManager;
		Ponto spawn;
	public:
		ShotManager* shotManager;
		Ponto camera;
		Game();
		void mainLoop();
		void desenhaMira(Ponto aim);
		Player *player;
		Mapa *mapa;
		void addPlatform(Platform* plat);
		GravityManager *gravityManager;
		void reloadLua();
		void removePlatforms();
		void setSpawn(Ponto spawn);
		Ponto getSpawn() {return spawn;}
};

#endif
