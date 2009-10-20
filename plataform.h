#ifndef PLATAFORM_H
#define PLATAFORM_H

#include "geometry.h"

class Plataform {
	private:
	Linha line;
	bool passable;
	public:
	Plataform(Linha aline);
	Linha getLine() {return line;};
	bool isPassable();
	void setPassable() {passable = true;}
	void desenha();
};

#endif
