#ifndef GAME_H
#define GAME_H

#include <string>
#include "gravity.h"
#include "mapa.h"
#include "weaponmanager.h"
#include "configmanager.h"
#include "collision.h"

class Player;
class Mapa;
class ShotManager;

class Game {
	private:
		void show();
		void loadMap(std::string mapname);
		std::string currentMap;
		Ponto spawn;
	public:
		ConfigManager *config;
		CollisionManager* collisionManager;
		WeaponManager* weaponManager;
		ShotManager* shotManager;
		double rate;
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
		void setSpawn(Ponto spawn);
		Ponto getSpawn() {return spawn;}
		void resize(GLsizei x, GLsizei y);
		WeaponItem* dropWeapon(std::string name);
};

#endif
