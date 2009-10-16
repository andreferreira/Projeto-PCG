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

Ponto Player::body() {
    Ponto corpo(CINTURA);
    return corpo;
}

Ponto Player::leftArm() {
    Ponto braco(-10,-30);
    return braco;
}

Ponto Player::rightArm() {
    Ponto braco(10,-30);
    return braco;
}

void Player::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		Ponto leftfeet = leftFeet();
		Ponto rightfeet = rightFeet();
		Ponto corpo = body();
		Ponto leftarm = leftArm();
		Ponto rightarm = rightArm();
		glBegin(GL_LINES);
			glVertex3f(corpo.x,corpo.y,0);
			glVertex3f(PESCOCO,0);

			glVertex3f(leftfeet.x,leftfeet.y,0);
            glVertex3f(CINTURA,0);

			glVertex3f(rightfeet.x,rightfeet.y,0);
            glVertex3f(CINTURA,0);

			glVertex3f(leftarm.x,leftarm.y,0);
			glVertex3f(PESCOCO,0);

			glVertex3f(rightarm.x,rightarm.y,0);
			glVertex3f(PESCOCO,0);
		glEnd();
		glPushMatrix();
            glTranslatef(0,-70,0);
            drawCircle(10,30);
        glPopMatrix();
	glPopMatrix();
}


Rect Player::getBaseRect() {
	Ponto leftfeet = leftFeet();
	Ponto rightfeet = rightFeet();
	Rect ret(leftfeet.x+getX(),leftfeet.y+getY(),rightfeet.x+getX(),-10+getY()+std::min(leftfeet.y,rightfeet.y));
	return ret;
}
