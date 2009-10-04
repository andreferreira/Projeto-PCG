#include "player.h"
#include "geometry.h"

void Player::desenha() {
	glPushMatrix();
		glTranslatef(posicao.x,posicao.y,0);
		drawCircle(10,30);
	glPopMatrix();
}
