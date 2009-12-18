#include "player.h"
#include "shot.h"

Player::Player(Game* agame, Ponto pos, Ponto speed): Shooter(agame, pos, speed) { 
	hp = MAXHP;
}

void Player::desenha() {
	game->desenhaMira(aim);
    Shooter::desenha();
}

void Player::collide(Thing *b) {
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot && shot->firedBy != this) {
		shot->dead = true;
		if (this->getPosition().x < shot->firedBy->getPosition().x)
			addToAngle -= 0.5;
		else
			addToAngle += 0.5;
		addToAngle = std::max(std::min(addToAngle, PI/2),-PI/2);
		hp -= shot->damage;
		if (hp <= 0) {
			dead = true;
		}
	}
}

void Player::drawEquipment() {
	glPushMatrix();
		Ponto hip = cintura();
		Ponto leftfeet = leftFeet();
		Ponto rightfeet = rightFeet();
		glTranslatef(hip.x,hip.y,0);
		glRotatef(bodyAngle*180.0/PI,0,0,1);
		glTranslatef(0,-11-30,0); //cabeca
		if (crawl)
			glRotatef(-bodyAngle*180.0/PI,0,0,1);
		glBegin(GL_POLYGON);
			glVertex3f(-11,-2,0);
			glVertex3f( 11,-2,0);
			glVertex3f( 11,-1,0);
			glVertex3f(-11,-1,0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(11,-2,0);
			glVertex3f(11, 2,0);
			glVertex3f( 2, 2,0);
			glVertex3f( 2,-2,0);
		glEnd();
	glPopMatrix();
}
