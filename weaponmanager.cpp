#include "weaponmanager.h"
#include "luaenv.h"
#include "weapon.h"
#include "weaponitem.h"
#include "game.h"
#include "shotmanager.h"
#include "shot.h"
#include "usereventtype.h"

WeaponManager::WeaponManager(Game* g) {
	lstate = NULL;
	game = g;
}

std::list<Weapon*> *_weapons = NULL;
Game *_game = NULL;
std::map<std::string, Polygon> *_collision = NULL;

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
	linha.color[0] = lua_tonumber(L, 6);
	linha.color[1] = lua_tonumber(L, 7);
	linha.color[2] = lua_tonumber(L, 8);
	w->sprite.addLinha(linha);
	return 0;
}

static int regspritelineshot (lua_State *L) {
	Shot* w = (Shot*)lua_touserdata(L, 1);
	Ponto a,b;
	a.x = lua_tonumber(L, 2);
	a.y = lua_tonumber(L, 3);
	b.x = lua_tonumber(L, 4);
	b.y = lua_tonumber(L, 5);
	Linha linha(a,b);
	linha.color[0] = lua_tonumber(L, 6);
	linha.color[1] = lua_tonumber(L, 7);
	linha.color[2] = lua_tonumber(L, 8);
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
	userevent.code = FUNCTIONCALL;
	userevent.data1 = (void*)deleteShotFunc;
	userevent.data2 = (void*)param;
	
	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);

	return 0;
}


static int createshot (lua_State *L) {
	double x,y,angle,rate,gravity,speed;
	int damage;
	Weapon* weapon;
	x = lua_tonumber(L, 1);
	y = lua_tonumber(L, 2);
	angle = lua_tonumber(L, 3);
	rate = lua_tonumber(L, 4);
	weapon = (Weapon*)lua_touserdata(L, 5);
	gravity = lua_tonumber(L, 6);
	speed = lua_tonumber(L, 7);
	damage = lua_tonumber(L, 8);
	
	x += weapon->position.x;
	y += weapon->position.y;
	
	Shot* newshot = new Shot(x,y,angle,speed,gravity,weapon,damage);
	weapon->game->shotManager->addShot(newshot);
	SDL_AddTimer(rate*_game->rate,deleteShotCallback,newshot);
	lua_pushlightuserdata(L, newshot);
	return 1;
}

static int regcollision(lua_State *L) {
	const char* nome = lua_tostring(L, 1);
	double x1, y1, x2, y2;
	x1 = lua_tonumber(L, 2);
	y1 = lua_tonumber(L, 3);
	x2 = lua_tonumber(L, 4);
	y2 = lua_tonumber(L, 5);
	Linha l(x1, y1, x2, y2);
	if (_collision->find(nome) == _collision->end()) {
		Polygon p;	
		(*_collision)[nome] = p;
	}
	(*_collision)[nome].addLinha(l);
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

Polygon WeaponManager::getCollision(std::string name) {
	return collision[name];
}

WeaponItem* WeaponManager::getItem(std::string name) {
	return new WeaponItem(getWeapon(name), getCollision(name));
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
	collision.clear();
	_collision = &collision;
	lstate = newState();
	registerFunction(lstate,"regweapon",regweapon);
	registerFunction(lstate,"regspriteline",regspriteline);
	registerFunction(lstate,"regspritelineshot",regspritelineshot);
	registerFunction(lstate,"regfirefunction",regfirefunction);
	registerFunction(lstate,"createshot",createshot);
	registerFunction(lstate,"regcollision",regcollision);
	doLuaFile(lstate,"weaponmanager.lua");
	doLuaFile(lstate,"weapons.lua");
}
