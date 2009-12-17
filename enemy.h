#ifndef ENEMY_H
#define ENEMY_H

#include "shooter.h"

class Enemy: public Shooter {
	public:
		Enemy(Game* agame);
		void die();
		void think();
		double distanceFromPlayer();
		virtual void collide(Thing *b);
};

#endif
