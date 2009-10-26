#ifndef THING_H
#define THING_H

#include "geometry.h"

class Thing {
	private:
		Ponto posicao;
		Vetor velocidade;
	public:
		bool onGround;
		bool bypass;
		Thing();
		void addSpeed(double xspeed, double yspeed);
		void setSpeed(double xspeed, double yspeed);
		double getSpeedX() {return velocidade.x;}
		double getSpeedY() {return velocidade.y;}
		void setPosition(double x, double y);
		double getX() {return posicao.x;}
		double getY() {return posicao.y;}
		void move();
		virtual Linha getBaseLine();
};


#endif
