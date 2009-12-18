#include <algorithm>

#include "enemymanager.h"
#include "enemy.h"
#include "game.h"

static int regenemy (lua_State *L) {
	lua_settable(L, LUA_REGISTRYINDEX);
}

EnemyManager::EnemyManager(Game* g) {
	game = g;
	lstate = NULL;
}

void EnemyManager::loadEnemies() {
	std::set<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		(*it)->die();
	}
	enemies.clear();
	if (lstate != NULL)
		lua_close(lstate);
	lstate = newState();
	registerFunction(lstate,"regenemy",regenemy);
	doLuaFile(lstate,"enemymanager.lua");
	doLuaFile(lstate,"enemies.lua");
}

void EnemyManager::desenha() {
	std::set<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		(*it)->desenha();
	}
}

void EnemyManager::move() {
	std::set<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		(*it)->move();
	}
}

void EnemyManager::animate() {
	std::set<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		(*it)->animate();
	}
}

void EnemyManager::think() {
	std::set<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		(*it)->think();
	}
}

void EnemyManager::remove(Enemy* enemy) {
	enemies.erase(enemies.find(enemy));
}

Enemy* EnemyManager::createEnemy(std::string name) {
	lua_pushstring(lstate,name.c_str());
	lua_gettable(lstate, LUA_REGISTRYINDEX);
	if (lua_pcall(lstate,0,2,0) != 0)  /* do the call */
        printf("error: %s", lua_tostring(lstate, -1));
	std::string weaponname = lua_tostring(lstate, 1);
	lua_pop(lstate,2);
	Enemy* ret = new Enemy(game);
	enemies.insert(ret);
	game->gravityManager->subscribe(ret);
	game->collisionManager->subscribe(ret);
	ret->equip(game->weaponManager->getWeapon(weaponname));
	return ret;
}

bool enemyAlive(Enemy* e) {
	return !e->dead;
}

bool EnemyManager::hasEnemies() {
	if (enemies.empty())
		return false;
	return count_if(enemies.begin(), enemies.end(), enemyAlive) > 0;
}
