#ifndef SHOT_H
#define SHOT_H

#include "thing.h"

class Weapon;
class ShotManager;

class Shot: public Thing {
	private:
	Weapon* weapon;
	public:
	ShotManager* shotManager;
	void desenha();
	Shot(double x, double y, double angle, Weapon* w, ShotManager* s);
};

#endif
