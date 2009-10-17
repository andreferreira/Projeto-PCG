#include "thing.h"

Thing::Thing() {
	onGround = false;
}

void Thing::addSpeed(double xspeed, double yspeed) {
	velocidade.x += xspeed;
	velocidade.y += yspeed;
}

void Thing::setSpeed(double xspeed, double yspeed) {
	velocidade.x = xspeed;
	velocidade.y = yspeed;
}

void Thing::setPosition(double x, double y) {
	posicao.x = x;
	posicao.y = y;
}

void Thing::move() {
	posicao.x += velocidade.x;
	posicao.y += velocidade.y;
}

Linha Thing::getBaseLine() {
	Linha ret(0,0,0,0);
	return ret;
}
