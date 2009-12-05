#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include "luaenv.h"

class Enemy;
class Game;

class EnemyManager {
	private:
		lua_State* lstate;
		Game* game;
		std::vector<Enemy*> enemies;
	public:
		EnemyManager(Game* g);
		void loadEnemies();
		Enemy* createEnemy(std::string name);
		void desenha();
};

#endif
