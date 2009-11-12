#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <list>
#include <string>

class Weapon;
struct lua_State;

class WeaponManager {
	private:
		std::list<Weapon*> weapons;
		lua_State* lstate;
	public:
		WeaponManager();
		void loadWeapons();
		Weapon* getWeapon(std::string name);
};
	

#endif
