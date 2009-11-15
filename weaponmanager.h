#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <list>
#include <string>

class Weapon;
class Game;
struct lua_State;

class WeaponManager {
	private:
		std::list<Weapon*> weapons;
		lua_State* lstate;
		Game* game;
	public:
		WeaponManager(Game* g);
		void loadWeapons();
		Weapon* getWeapon(std::string name);
};
	

#endif
