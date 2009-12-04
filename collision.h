#ifndef COLLISION_H
#define COLLISION_H

#include <set>
#include "thing.h"

class CollisionManager {
	private:
		std::set<Thing*> things;
	public:
		bool checkCollision(Thing* a, Thing* b);
		void subscribe(Thing* thing);
		void remove(Thing* thing);
		void update();
};

#endif
