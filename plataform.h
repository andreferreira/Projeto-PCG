#ifndef PLATAFORM_H
#define PLATAFORM_H

#include "geometry.h"

class Plataform {
	private:
	Linha line;
	bool passable;
	public:
	Plataform(Linha aline, bool pass);
	Linha getLine() {return line;};
	bool isPassable() {return passable;};
	void setPassable() {passable = true;}
	void desenha();
};

#endif
