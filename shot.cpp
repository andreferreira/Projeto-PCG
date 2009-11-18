#include "shot.h"
#include "weapon.h"
#include "game.h"
#include "shotmanager.h"
#include "collision.h"
#include "player.h"
#include <math.h>

Shot::Shot(double x, double y, double angle, double speed, double gravity, Weapon* w) {
	game = w->game;
	setPosition(x,y);
	if (gravity != 0.0)
		game->gravityManager->subscribe(this);
	game->collisionManager->subscribe(this);
	gravityRate = gravity;
	bypass = true;
	setSpeed(-cos(angle)*speed,sin(angle)*speed);
}

Shot::~Shot() {
	game->shotManager->deleteShot(this);
	game->collisionManager->remove(this);
	if (gravityRate != 0.0)
		game->gravityManager->deleteThing(this);
}

void Shot::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		sprite.desenha();
	glPopMatrix();
}

Polygon Shot::getCollision() {
	Ponto atual(getX(),getY());
	Polygon collisionSprite = sprite;
	for (int i = 0; i < collisionSprite.linhas.size();i++) {
		collisionSprite.linhas[i].vertices[0] = collisionSprite.linhas[i].vertices[0] + atual;
		collisionSprite.linhas[i].vertices[1] = collisionSprite.linhas[i].vertices[1] + atual;
	}
	return collisionSprite;
}

#include <iostream>

void Shot::collide(Thing* b){
	Player* p;
	if (p = dynamic_cast<Player*>(b)) {
		std::cout<<"Player deaded "<<p<<std::endl;
	}
}
