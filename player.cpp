#include "player.h"

Player::Player(int x, int y) {
    posicao.x = x;
    posicao.y = y;
    velocidade.x = 1;
    velocidade.y = 1;
}

void Player::desenha() {
	glPushMatrix();
		glTranslatef(posicao.x,posicao.y,0);
		drawCircle(10,30);
	glPopMatrix();
}

void Player::move(int x, int y) {
    posicao.x += velocidade.x * x;
    posicao.y += velocidade.y * y;
}
