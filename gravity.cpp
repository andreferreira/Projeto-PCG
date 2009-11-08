#include "gravity.h"
#include <iostream>

void GravityManager::subscribe(Thing* thing) {
	things.insert(thing);
}

void GravityManager::addPlatform(Platform* linha) {
	platforms.insert(linha);
}

void GravityManager::update() {
	std::set<Thing*>::iterator it;
	std::set<Platform*>::iterator plat;
	for (it = things.begin(); it != things.end(); it++) {
		(*it)->addSpeed(0,0.1);
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
			(*it)->bypass = false;
			(*it)->onGround = false;
		}
	}
}

bool contido(double x1,double y1, double x2, double y2, Ponto &ponto) {
	return x1 <= ponto.x && ponto.x <= x2 && y1 <= ponto.y && ponto.y <= y2;
}

//calcula se a direcao dos segmentos p0p1 p1p2 é horaria, antihoraria ou se sao colineares
double direction(const Ponto &p0,const Ponto &p1,const Ponto &p2) {
	return (p2 - p0) * (p1 - p0);
}

bool onsegment(const Ponto &pi,const Ponto &pj,const Ponto &pk) { 
	if ((std::min(pi.x, pj.x) <= pk.x && pk.x <= std::max(pi.x, pj.x)) &&
	    (std::min(pi.y, pj.y) <= pk.y && pk.y <= std::max(pi.y, pj.y)))
		return true; 
	else 
		return false;
}

bool linesIntersect(const Linha a,const Linha b) {
	Ponto p1 = a.vertices[0];
	Ponto p2 = a.vertices[1];
	Ponto p3 = b.vertices[0];
	Ponto p4 = b.vertices[1];
	double d1 = direction(p3, p4, p1);
	double d2 = direction(p3, p4, p2);
	double d3 = direction(p1, p2, p3);
	double d4 = direction(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
	   ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true; 
	else if (d1 == 0.0 && onsegment(p3, p4, p1)) 
		return true;
	else if (d2 == 0.0 && onsegment(p3, p4, p2))
		return true; 
	else if (d3 == 0.0 && onsegment(p1, p2, p3))
		return true; 
	else if (d4 == 0.0 && onsegment(p1, p2, p4))
		return true;
	else
		return false;
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
