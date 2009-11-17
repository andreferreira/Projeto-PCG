#ifndef SHOT_H
#define SHOT_H

#include "thing.h"

class Weapon;
class Game;

class Shot: public Thing {
	private:
	Game* game;
	public:
	Polygon sprite;
	Shot(double x, double y, double angle, double speed, double gravityRate, Weapon* w);
	~Shot();
	void desenha();
};

#endif
