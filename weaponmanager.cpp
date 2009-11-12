#include "weaponmanager.h"
#include "luaenv.h"
#include "weapon.h"

WeaponManager::WeaponManager() {
	lstate = NULL;
}

std::list<Weapon*> *_weapons = NULL;

static int regweapon (lua_State *L) {
	Ponto r,l;
	r.x = lua_tonumber(L, 1);
	r.y = lua_tonumber(L, 2);
	l.x = lua_tonumber(L, 3);
	l.y = lua_tonumber(L, 4);
	Weapon* newweapon = new Weapon();
	newweapon->name = lua_tostring (L, 5);
	newweapon->setRightHand(r);
	newweapon->setLeftHand(l);
	Weapon** instack = (Weapon**)lua_newuserdata(L, sizeof(Weapon*));
	*instack = newweapon;
	_weapons->push_front(newweapon);
	return 1;
}

static int regspriteline (lua_State *L) {
	Weapon* w = *(Weapon **)(Weapon*)lua_touserdata(L, 1);
	Ponto a,b;
	a.x = lua_tonumber(L, 2);
	a.y = lua_tonumber(L, 3);
	b.x = lua_tonumber(L, 4);
	b.y = lua_tonumber(L, 5);
	Linha linha(a,b);
	w->sprite.addLinha(linha);
	return 0;
}

Weapon* WeaponManager::getWeapon(std::string name) {
	std::list<Weapon*>::iterator it;
	for (it = weapons.begin(); it != weapons.end(); it++) {
		if ((*it)->name == name)
			return (*it);
	}
	return NULL;
}

void WeaponManager::loadWeapons() {
	if (lstate != NULL)
		lua_close(lstate);
	_weapons = &weapons;
	lstate = newState();
	registerFunction(lstate,"regweapon",regweapon);
	registerFunction(lstate,"regspriteline",regspriteline);
	doLuaFile(lstate,"weaponmanager.lua");
	doLuaFile(lstate,"weapons.lua");
}
