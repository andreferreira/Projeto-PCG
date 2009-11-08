#ifndef PLATAFORM_H
#define PLATAFORM_H

#include "geometry.h"

class Platform {
	private:
	Linha line;
	bool passable;
	public:
	Platform(Linha aline, bool pass);
	Linha getLine() {return line;};
	bool isPassable() {return passable;};
	void setPassable() {passable = true;}
	void desenha();
};

#endif
