#include "gravity.h"
#include <iostream>

void GravityManager::subscribe(Thing* thing) {
	things.insert(thing);
}

void GravityManager::addPlatform(Linha* linha) {
	plataforms.insert(linha);
}

void GravityManager::update() {
	std::set<Thing*>::iterator it;
	std::set<Linha*>::iterator plat;
	for (it = things.begin(); it != things.end(); it++) {
		if ((*it)->getSpeedY() > 0.6)
			(*it)->onGround = false;
		if ((*it)->getSpeedY() <= 0 && !(*it)->onGround) {
			(*it)->addSpeed(0,0.1);
			continue;
		}
		bool colisao = false;
		for (plat = plataforms.begin(); !colisao && plat != plataforms.end(); plat++) {
			colisao = checkGround(*it,*plat);
		}
		if (colisao) {
			//std::cout<<"colisao"<<std::endl;
			(*it)->onGround = true;
			(*it)->setSpeed((*it)->getSpeedX(),-0.2);
		}
		else {
			(*it)->addSpeed(0,0.1);
		}
	}
}

bool contido(double x1,double y1, double x2, double y2, Ponto &ponto) {
	return x1 <= ponto.x && ponto.x <= x2 && y1 <= ponto.y && ponto.y <= y2;
}


//xy1 é o canto debaixo esq, xy2 decima direito
bool collisionRectLine(double x1,double y1, double x2, double y2, Linha &linha) {
	if (contido(x1,y1,x2,y2,linha.vertices[0]) || contido(x1,y1,x2,y2,linha.vertices[1]))
		return true;
	double minxlinha = std::min(linha.vertices[0].x,linha.vertices[1].x);
	double minylinha = std::min(linha.vertices[0].y,linha.vertices[1].y);
	double maxxlinha = std::max(linha.vertices[0].x,linha.vertices[1].x);
	double maxylinha = std::max(linha.vertices[0].y,linha.vertices[1].y);
	//std::cout<<y1<<" "<<maxylinha<<" "<<y2<<" "<<minylinha<<" "<< x1<<" "<<maxxlinha<<" "<< x2 <<" "<<minylinha<<std::endl;
	if (y1 > maxylinha || y2 < minylinha || x1 > maxxlinha || x2 < minxlinha)
		return false;
	return true;
}


bool GravityManager::checkGround(Thing* thing, Linha* plataform) {
	Rect baseRect = thing->getBaseRect();
	return collisionRectLine(baseRect.vertices[0].x,baseRect.vertices[0].y,
							 baseRect.vertices[1].x,baseRect.vertices[1].y,*plataform);
}
