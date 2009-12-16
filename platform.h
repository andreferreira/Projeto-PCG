#ifndef PLATAFORM_H
#define PLATAFORM_H

#include "geometry.h"

class Platform {
	private:
	Linha line;
	bool passable;
	public:
	Platform(Linha aline, bool pass, double r, double g, double b);
	Linha getLine() {return line;};
	bool isPassable() {return passable;};
	void setPassable() {passable = true;}
	void desenha();
	double angle();
};

#endif
