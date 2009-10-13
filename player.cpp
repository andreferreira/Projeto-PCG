#include "player.h"

Player::Player(int x, int y) {
    posicao.x = x;
    posicao.y = y;
    velocidade.x = 0;
    velocidade.y = 0;
}

void Player::desenha() {
	glPushMatrix();
		glTranslatef(posicao.x,posicao.y,0);
		drawCircle(10,30);
	glPopMatrix();
}
