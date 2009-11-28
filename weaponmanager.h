#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <map>
#include <list>
#include <string>

#include "geometry.h"

class Weapon;
class WeaponItem;
class Game;
struct lua_State;

class WeaponManager {
	private:
		std::list<Weapon*> weapons;
		lua_State* lstate;
		Game* game;
		std::map<std::string, Polygon> collision;
	public:
		WeaponManager(Game* g);
		void loadWeapons();
		Weapon* getWeapon(std::string name);
		Polygon getCollision(std::string name);
		WeaponItem* getItem(std::string name);
};

#endif
