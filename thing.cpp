#include "thing.h"

Thing::Thing() {
	onGround = false;
	maxspeed.x = 99999;
	maxspeed.y = 99999;
}

void Thing::addSpeed(double xspeed, double yspeed) {
	setSpeed(velocidade.x+xspeed,velocidade.y+yspeed);
}

void Thing::setSpeed(double xspeed, double yspeed) {
	velocidade.x = std::max(std::min(xspeed,maxspeed.x),-maxspeed.x);
	velocidade.y = std::max(std::min(yspeed,maxspeed.y),-maxspeed.y);
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
