#ifndef THING_H
#define THING_H

#include "geometry.h"

class Thing {
	private:
		Ponto posicao;
		Vetor velocidade;
	public:
		Thing();
		void addSpeed(double xspeed, double yspeed);
		void setSpeed(double xspeed, double yspeed);
		void setPosition(double x, double y);
		double getX() {return posicao.x;}
		double getY() {return posicao.y;}
		void move();
};


#endif
