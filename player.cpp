#include "player.h"
#include "gravity.h"

Player::Player(Game* agame) {
    setPosition(0,0);
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


