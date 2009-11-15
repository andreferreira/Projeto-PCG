#include "shot.h"
#include "weapon.h"
#include "game.h"
#include "shotmanager.h"
#include <math.h>

Shot::Shot(double x, double y, double angle, double gravity, Weapon* w) {
	weapon = w;
	setPosition(x,y);
	if (gravity != 0.0)
		weapon->game->gravityManager->subscribe(this);
	gravityRate = gravity;
	bypass = true;
	setSpeed(-cos(angle)*weapon->shotSpeed,sin(angle)*weapon->shotSpeed);
}

Shot::~Shot() {
	weapon->game->shotManager->deleteShot(this);
	if (gravityRate != 0.0)
		weapon->game->gravityManager->deleteThing(this);
}

void Shot::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		drawCircle(1,30);
	glPopMatrix();
}
