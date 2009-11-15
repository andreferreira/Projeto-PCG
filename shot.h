#ifndef SHOT_H
#define SHOT_H

#include "thing.h"

class Weapon;

class Shot: public Thing {
	private:
	Weapon* weapon;
	public:
	Shot(double x, double y, double angle, double speed, double gravityRate, Weapon* w);
	~Shot();
	void desenha();
};

#endif
