#ifndef SHOT_H
#define SHOT_H

#include "thing.h"

class Weapon;
class Game;
class Shooter;

class Shot: public Thing {
	private:
	Game* game;
	public:
	Shooter* firedBy;
	Polygon sprite;
	Shot(double x, double y, double angle, double speed, double gravityRate, Weapon* w);
	~Shot();
	void desenha();
	virtual Polygon getCollision();
	virtual void collide(Thing* b);
};

#endif
