#include "shot.h"
#include "weapon.h"
#include "game.h"
#include "shotmanager.h"
#include "collision.h"
#include "player.h"
#include "shooter.h"
#include "enemy.h"
#include <math.h>

Shot::Shot(double x, double y, double angle, double speed, double gravity, Weapon* w) {
	game = w->game;
	firedBy = w->firedBy;
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
	Polygon collisionSprite = sprite;
	return collisionSprite;
}

void Shot::collide(Thing* b){
	if (dead) return;
	/*Player* p = dynamic_cast<Player*>(b);
	
	Enemy* e = dynamic_cast<Enemy*>(b);
	std::cout<<b<<std::endl;
	if (p ) {
	}
	else if (e ) {
		e->die();
		
	}*/
}
