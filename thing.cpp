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
	velocidade.x = xspeed;
	velocidade.y = yspeed;
}

void Thing::setPosition(double x, double y) {
	posicao.x = x;
	posicao.y = y;
}

void Thing::move() {
	posicao.x += std::max(std::min(velocidade.x,maxspeed.x),-maxspeed.x);
	posicao.y += std::max(std::min(velocidade.y,maxspeed.y),-maxspeed.y);
}

Linha Thing::getBaseLine() {
	Linha ret(0,0,0,0);
	return ret;
}
