#ifndef GEOMETRIA_H
#define GEOMETRIA_H
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

struct Ponto { 
	double x,y;
	Ponto () { }
	Ponto (double x1, double y1) {x = x1; y = y1;}
};

struct Vetor { 
	double x,y;
};

class Linha {
	public:
	Ponto vertices[2];

	void desenha();
	Linha(double x1,double y1,double x2, double y2);
	Linha(Ponto a, Ponto b) {vertices[0] = a; vertices[1] = b;}
};

class Rect {
	private:
		void normaliza();
	public:
	Ponto vertices[2];
	Rect(double x1,double y1,double x2, double y2);
	Rect(Ponto a, Ponto b) {vertices[0] = a; vertices[1] = b; normaliza();}
};

void drawCircle(double radius, int lines);

#endif
