#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

struct Ponto { 
	double x,y;
};

class Plataforma {
	public:
	void desenha();
	Plataforma(double x1,double y1,double x2, double y2);
	private:
	Ponto vertices[2];
};

#endif
