#ifndef GEOMETRIA_H
#define GEOMETRIA_H
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

struct Ponto { 
	double x,y;
};

struct Vetor { 
	double x,y;
};

class Linha {
	private:
	Ponto vertices[2];
	public:
	void desenha();
	Linha(double x1,double y1,double x2, double y2);
	Linha(Ponto a, Ponto b) {vertices[0] = a; vertices[1] = b;}
};

void drawCircle(double radius, int lines);

#endif
