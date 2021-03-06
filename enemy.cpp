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
#include <iostream>
void Enemy::think() {
	addSpeed(closerToZero(-getSpeedX(),sign(getSpeedX())*-0.5),0);
	crawl = false;
	if (dead) return;
	Player *player = game->player;
	Ponto playerpos = player->getPosition();
	if (playerpos.x < getPosition().x)
		direction = -1;
	else
		direction = 1;
	if (playerpos.y < getPosition().y  && (!onGround || player->onGround) && getSpeedY() > -4) {
		addSpeed( 0, -1);
	}
	if (distanceFromPlayer() >= 500)
		return;
	if (player->crawl && onGround)
		crawl = true;
	if (playerpos.y > getPosition().y + 30 && distanceFromPlayer() <= 200)
		bypass = true;
	else
		bypass = false;
	if (distanceFromPlayer() <= 300 && distanceFromPlayer() >= 200)
		addSpeed( direction*3, 0);
	Ponto leftfeet = player->leftFeet();
	Ponto rightfeet = player->rightFeet();
	setAim(playerpos.x + player->pescoco().x,playerpos.y+player->pescoco().y + std::min(-rightfeet.y,-leftfeet.y));
	fire();
}

void Enemy::collide(Thing* b) {
	if (dead) return;
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot && shot->firedBy == game->player) {
		this->die();
	}
	Shooter* shooter = dynamic_cast<Shooter*>(b);
	if (shooter) {
		if (shooter->getPosition().x > getPosition().x)
			addSpeed(-2,0);
		else
			addSpeed(2,0);
	}
}

void Enemy::drawEquipment() {
	glPushMatrix();
		Ponto hip = cintura();
		Ponto leftfeet = leftFeet();
		Ponto rightfeet = rightFeet();
		glTranslatef(hip.x,hip.y,0);
		glRotatef(bodyAngle*180.0/PI,0,0,1);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0,0,0);
			glVertex3f(-10,0,0);
			glVertex3f(-10,-30,0);
			glVertex3f(0,-30,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-2.5,0,0);
			glVertex3f(-7.5,0,0);
			glVertex3f(-7.5,5,0);
			glVertex3f(-2.5,5,0);
		glEnd();
	glPopMatrix();
}
