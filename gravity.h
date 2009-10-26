#ifndef GRAVITY_H
#define GRAVITY_H

#include <set>
#include "geometry.h"
#include "thing.h"
#include "plataform.h"

class GravityManager {
	private:
		std::set<Thing*> things;
		std::set<Plataform*> plataforms;
		bool checkGround(Thing* thing, Plataform *plataform);
	public:
		void subscribe(Thing* thing);
		void addPlatform(Plataform* linha);
		void update();
};

#endif
