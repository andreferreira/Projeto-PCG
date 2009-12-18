#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <set>
#include "luaenv.h"

class Enemy;
class Game;

class EnemyManager {
	private:
		lua_State* lstate;
		Game* game;
		std::set<Enemy*> enemies;
	public:
		EnemyManager(Game* g);
		void loadEnemies();
		Enemy* createEnemy(std::string name);
		void animate();
		void think();
		void desenha();
		void move();
		void remove(Enemy* enemy);
		bool hasEnemies();
};

#endif
