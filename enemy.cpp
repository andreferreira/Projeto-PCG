#include "enemy.h"
#include "shot.h"
 
Enemy::Enemy(Game* agame): Shooter(agame, Ponto(0,0), Ponto(0,0)) {
	dead = false;
}

void Enemy::die() {
	if (dead) return;
	dead = true;
	game->enemyManager->remove(this);
	game->gravityManager->deleteThing(this);
	game->collisionManager->remove(this);
}

void Enemy::think() {
	if (dead) return;
}

void Enemy::collide(Thing* b) {
	if (dead) return;
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot && shot->firedBy != this) {
		this->die();
	}
}
