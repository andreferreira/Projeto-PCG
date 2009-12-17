#ifndef THING_H
#define THING_H

#include "geometry.h"

class Thing {
	protected:
		Ponto posicao;
		Ponto velocidade;
		Ponto maxspeed;
	public:
		bool dead;
		double gravityRate;
		bool onGround;
		bool bypass;
		Thing();
		void addSpeed(double xspeed, double yspeed);
		void setSpeed(double xspeed, double yspeed);
		double getSpeedX() {return velocidade.x;}
		double getSpeedY() {return velocidade.y;}
		Ponto getSpeed() {return velocidade;}
		void setPosition(double x, double y);
		Ponto getPosition() {return posicao;}
		double getX() {return posicao.x;}
		double getY() {return posicao.y;}
		void move();
		virtual Linha getBaseLine();
		virtual Polygon getCollision();
		virtual void collide(Thing* b);
		virtual bool canCollide(Thing* b);
};


#endif
