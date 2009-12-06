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
				static int counter = 0;
				counter++;
				timeToCollide = t;
				collidedWith = *plat;
				double slope = collidedWith->angle() / (PI/2);
				if (slope != 1)
					(*it)->onGround = true;
				if (slope == 1) {
					(*it)->setSpeed(sign((*it)->getSpeedX())*-0.01,(*it)->getSpeedY());
				}
				else if (slope == 0 && (*it)->getSpeedY() > 0.0) {
					(*it)->setSpeed((*it)->getSpeedX(),(*it)->getSpeedY()*timeToCollide);
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
	return (!platform->isPassable() || !thing->bypass) && (
	           0<= t && t <= 1.0); 
}
