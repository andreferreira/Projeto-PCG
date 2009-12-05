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
	std::vector<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		delete (*it);
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
	std::vector<Enemy*>::iterator it;
	for (it = enemies.begin();it != enemies.end(); it++) {
		(*it)->desenha();
	}
}

Enemy* EnemyManager::createEnemy(std::string name) {
	lua_pushstring(lstate,name.c_str());
	lua_gettable(lstate, LUA_REGISTRYINDEX);
	if (lua_pcall(lstate,0,2,0) != 0)  /* do the call */
        printf("error: %s", lua_tostring(lstate, -1));
	std::string weaponname = lua_tostring(lstate, 1);
	Enemy* ret = new Enemy(game);
	enemies.push_back(ret);
	ret->equip(game->weaponManager->getWeapon(weaponname));
	return ret;
}
