#include "enemy.h"
#include "shot.h"
#include "player.h"

Enemy::Enemy(Game* agame): Shooter(agame, Ponto(0,0), Ponto(0,0)) {
}

void Enemy::die() {
	if (dead) return;
	dead = true;
	game->enemyManager->remove(this);
	game->gravityManager->deleteThing(this);
	//game->collisionManager->remove(this);
}

void Enemy::think() {
	if (dead) return;
	if (game->player->getPosition().x < this->getPosition().x)
		direction = -1;
	else
		direction = 1;
	setAim(game->player->getPosition().x,game->player->getPosition().y-50);
	fire();
}

void Enemy::collide(Thing* b) {
	if (dead) return;
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot && shot->firedBy == game->player) {
		this->die();
	}
}
