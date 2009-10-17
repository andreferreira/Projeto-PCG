#ifndef GRAVITY_H
#define GRAVITY_H

#include <set>
#include "geometry.h"
#include "thing.h"

class GravityManager {
	private:
		std::set<Thing*> things;
		std::set<Linha*> plataforms;
		bool checkGround(Thing* thing, Linha &plataform);
	public:
		void subscribe(Thing* thing);
		void addPlatform(Linha* linha);
		void update();
};

#endif
