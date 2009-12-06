#include "gravity.h"
#include <math.h>

void GravityManager::subscribe(Thing* thing) {
	things.insert(thing);
}

void GravityManager::addPlatform(Platform* linha) {
	platforms.insert(linha);
}

void GravityManager::deleteThing(Thing* thing) {
	things.erase(things.find(thing));
}

void GravityManager::update() {
	std::set<Thing*>::iterator it;
	std::set<Platform*>::iterator plat;
	for (it = things.begin(); it != things.end(); it++) {
		(*it)->addSpeed(0,(*it)->gravityRate);
		double timeToCollide = 9999;
		Platform* collidedWith = NULL;
		(*it)->onGround = false;
		for (plat = platforms.begin(); plat != platforms.end(); plat++) {
			double t;
			if (checkGround(*it, *plat, t)) {
				timeToCollide = t;
				collidedWith = *plat;
				double angle = collidedWith->angle();
				double slope = angle / (PI/2);
				if (slope != 1)
					(*it)->onGround = true;
				if (slope == 1) { //colisao com parede
					double dir = sign((*it)->getSpeedX());
					(*it)->setSpeed(dir*-3,(*it)->getSpeedY());
				}
				else if ((*it)->getSpeedY() >= (*it)->gravityRate) {
					(*it)->setSpeed((*it)->getSpeedX(),(*it)->getSpeedY()*timeToCollide);
				}
				if ((*it)->getSpeedY() < 0) {
				}
			}
		}
	}
}

void GravityManager::removePlatforms() {
	platforms.clear();
}

//caso ocorra colisao, t retorna em quanto tempo ela ocorrera
bool GravityManager::checkGround(Thing* thing, Platform *platform, double &t) {
	if (platform->isPassable() && thing->bypass)
		return false;
	Linha l1 = thing->getBaseLine();
	l1.translate(thing->getPosition());
	Linha l2 = l1;
	l2.translate(thing->getSpeed());
	Linha l3(l1.vertices[0],l2.vertices[0]);
	Linha l4(l1.vertices[1],l2.vertices[1]);
	Linha plat = platform->getLine();
	t = 9999;
	if (linesIntersect(l1,plat))
		t = 0;
	else {
		if (linesIntersect(l3,plat))
			t = std::min(t,timeToIntersection(l3,plat));
		if (linesIntersect(l4,plat))
			t = std::min(t,timeToIntersection(l4,plat));
		if (linesIntersect(l2,plat))
			t = std::min(t,1.0);
	}
	return (0<= t && t <= 1.0); 
}
