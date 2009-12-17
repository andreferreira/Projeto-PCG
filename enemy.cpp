#include "enemy.h"
#include "shot.h"
#include "player.h"

Enemy::Enemy(Game* agame): Shooter(agame, Ponto(0,0), Ponto(0,0)) {
}

void Enemy::die() {
	if (dead) return;
	dead = true;
	//game->enemyManager->remove(this);
	//game->gravityManager->deleteThing(this);
	//game->collisionManager->remove(this);
}

double Enemy::distanceFromPlayer() {
	return distance(game->player->getPosition(), this->getPosition());
}

void Enemy::think() {
	if (dead) return;
	Player *player = game->player;
	if (player->getPosition().x < this->getPosition().x)
		direction = -1;
	else
		direction = 1;
	if (distanceFromPlayer() >= 500)
		return;
	if (player->crawl && onGround) {
		crawl = true;
	}
	else
		crawl = false;
	setAim(player->getPosition().x + player->cintura().x,player->getPosition().y+player->cintura().y);
	fire();
}

void Enemy::collide(Thing* b) {
	if (dead) return;
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot && shot->firedBy == game->player) {
		this->die();
	}
}
