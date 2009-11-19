#include "gravity.h"
#include "game.h"

void GravityManager::subscribe(Thing* thing) {
	things.insert(thing);
}

void GravityManager::addPlatform(Platform* linha) {
	platforms.insert(linha);
}

void GravityManager::deleteThing(Thing* thing) {
	things.erase(things.find(thing));
}

void GravityManager::update(int t) {
	std::set<Thing*>::iterator it;
	std::set<Platform*>::iterator plat;
	for (it = things.begin(); it != things.end(); it++) {
		(*it)->addSpeed(0,(*it)->gravityRate*t/TIME_RATE);
		if ((*it)->getSpeedY() < 0.0) continue;
		bool colisao = false;
		for (plat = platforms.begin(); !colisao && plat != platforms.end(); plat++) {
			colisao = checkGround(*it, *plat);
		}
		if (colisao) {
			(*it)->onGround = true;
			(*it)->setSpeed((*it)->getSpeedX(),0.0);
		}
		else {
			(*it)->onGround = false;
		}
	}
}

void GravityManager::removePlatforms() {
	platforms.clear();
}

bool contido(double x1,double y1, double x2, double y2, Ponto &ponto) {
	return x1 <= ponto.x && ponto.x <= x2 && y1 <= ponto.y && ponto.y <= y2;
}

bool GravityManager::checkGround(Thing* thing, Platform *platform) {
	Linha baseLine = thing->getBaseLine();
	Linha l1 = baseLine;
	Linha l2(baseLine.vertices[0].x + thing->getSpeedX(),
	         baseLine.vertices[0].y + thing->getSpeedY(),
			 baseLine.vertices[1].x + thing->getSpeedX(),
			 baseLine.vertices[1].y + thing->getSpeedY());
	Linha l3(l1.vertices[0],l2.vertices[0]);
	Linha l4(l1.vertices[1],l2.vertices[1]);
	return (!platform->isPassable() || !thing->bypass) && (
	           linesIntersect(l1,platform->getLine()) ||
	           linesIntersect(l2,platform->getLine()) ||
		       linesIntersect(l3,platform->getLine()) ||
		       linesIntersect(l4,platform->getLine()));
}
