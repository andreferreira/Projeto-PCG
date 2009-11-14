#include "shot.h"
#include "weapon.h"
#include <math.h>
#include <iostream>
Shot::Shot(double x, double y, double angle, Weapon* w, ShotManager* s) {
	weapon = w;
	shotManager = s;
	setPosition(x,y);
	setSpeed(-cos(angle)*weapon->shotSpeed,sin(angle)*weapon->shotSpeed);
}

void Shot::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		drawCircle(1,30);
	glPopMatrix();
}
