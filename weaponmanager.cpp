#include "weaponmanager.h"
#include "luaenv.h"
#include "weapon.h"
#include "game.h"
#include "shotmanager.h"
#include "shot.h"

WeaponManager::WeaponManager(Game* g) {
	lstate = NULL;
	game = g;
}

std::list<Weapon*> *_weapons = NULL;
Game *_game = NULL;

static int regweapon (lua_State *L) {
	Ponto r,l,tip;
	r.x = lua_tonumber(L, 1);
	r.y = lua_tonumber(L, 2);
	l.x = lua_tonumber(L, 3);
	l.y = lua_tonumber(L, 4);
	Weapon* newweapon = new Weapon(_game,L);
	newweapon->name = lua_tostring (L, 5);
	newweapon->fireRate = lua_tonumber(L, 6);
	tip.x = lua_tonumber(L, 7);
	tip.y = lua_tonumber(L, 8);
	newweapon->shotSpeed = 10;
	newweapon->setRightHand(r);
	newweapon->setLeftHand(l);
	newweapon->setTip(tip);
	lua_pushlightuserdata(L, newweapon);
	_weapons->push_front(newweapon);
	return 1;
}

static int regfirefunction (lua_State *L) {
	lua_settable(L, LUA_REGISTRYINDEX);
}

static int regspriteline (lua_State *L) {
	Weapon* w = (Weapon*)lua_touserdata(L, 1);
	Ponto a,b;
	a.x = lua_tonumber(L, 2);
	a.y = lua_tonumber(L, 3);
	b.x = lua_tonumber(L, 4);
	b.y = lua_tonumber(L, 5);
	Linha linha(a,b);
	w->sprite.addLinha(linha);
	return 0;
}

static void deleteShotFunc(void* param) {
	Shot* shot = (Shot*) param;
	delete shot;
}

static Uint32 deleteShotCallback(Uint32 interval, void *param) {
	SDL_Event event;
	SDL_UserEvent userevent;
	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = (void*)deleteShotFunc;
	userevent.data2 = (void*)param;
	
	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);

	return 0;
}


static int createshot (lua_State *L) {
	double x,y,angle,rate,gravity;
	Weapon* weapon;
	x = lua_tonumber(L, 1);
	y = lua_tonumber(L, 2);
	angle = lua_tonumber(L, 3);
	rate = lua_tonumber(L, 4);
	weapon = (Weapon*)lua_touserdata(L, 5);
	gravity = lua_tonumber(L, 6);
	
	Shot* newshot = new Shot(x,y,angle,gravity,weapon);
	weapon->game->shotManager->addShot(newshot);
	SDL_AddTimer(rate,deleteShotCallback,newshot);
			
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
	std::list<Weapon*>::iterator it;
	for (it = weapons.begin(); it != weapons.end(); it++)
		delete (*it);
	weapons.clear();
	_weapons = &weapons;
	_game = game;
	lstate = newState();
	registerFunction(lstate,"regweapon",regweapon);
	registerFunction(lstate,"regspriteline",regspriteline);
	registerFunction(lstate,"regfirefunction",regfirefunction);
	registerFunction(lstate,"createshot",createshot);
	doLuaFile(lstate,"weaponmanager.lua");
	doLuaFile(lstate,"weapons.lua");
}
