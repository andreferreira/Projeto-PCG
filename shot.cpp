#include "shot.h"
#include "weapon.h"
#include "game.h"
#include "shotmanager.h"
#include <math.h>

Shot::Shot(double x, double y, double angle, double speed, double gravity, Weapon* w) {
	game = w->game;
	setPosition(x,y);
	if (gravity != 0.0)
		game->gravityManager->subscribe(this);
	gravityRate = gravity;
	bypass = true;
	setSpeed(-cos(angle)*speed,sin(angle)*speed);
}

Shot::~Shot() {
	game->shotManager->deleteShot(this);
	if (gravityRate != 0.0)
		game->gravityManager->deleteThing(this);
}

void Shot::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		sprite.desenha();
	glPopMatrix();
}
