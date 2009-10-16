#include "player.h"
#include "gravity.h"

Player::Player(Game* agame) {
    setPosition(40,40);
    setSpeed(0,0);
	game = agame;
	game->gravityManager->subscribe(this);
}

Ponto Player::leftFeet() {
	Ponto pe(-10,0);
	return pe;
}

Ponto Player::rightFeet() {
	Ponto pe(10,0);
	return pe;
}

void Player::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		Ponto leftfeet = leftFeet();
		Ponto rightfeet = rightFeet();
		glBegin(GL_LINES);
			glVertex3f(leftfeet.x,leftfeet.y,0);
			glVertex3f(0,-30,0);
			glVertex3f(rightfeet.x,rightfeet.y,0);
			glVertex3f(0,-30,0);
			//bracos aqui
		glEnd();//depois uma cabeça
		//drawCircle(10,30);
	glPopMatrix();
}


Rect Player::getBaseRect() {
	Ponto leftfeet = leftFeet();
	Ponto rightfeet = rightFeet();
	Rect ret(leftfeet.x+getX(),leftfeet.y+getY(),rightfeet.x+getX(),-10+getY()+std::min(leftfeet.y,rightfeet.y));
	return ret;
}
