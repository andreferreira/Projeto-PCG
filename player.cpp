#include "player.h"
#include "gravity.h"

Player::Player(Game* agame) {
    setPosition(40,40);
    setSpeed(0,0);
	game = agame;
	game->gravityManager->subscribe(this);
}

void Player::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		drawCircle(10,30);
	glPopMatrix();
}


Rect Player::getBaseRect() {
	Rect ret(-10+getX(),-10+getY(),10+getX(),10+getY());
	return ret;
}
