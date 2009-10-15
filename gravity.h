#ifndef GRAVITY_H
#define GRAVITY_H

#include <set>
#include "geometry.h"
#include "thing.h"

class GravityManager {
	private:
		std::set<Thing*> things;
		std::set<Linha*> plataforms;
		void checkGround(Thing* thing);
	public:
		void subscribe(Thing* thing);
		void addPlataform(Linha* linha);
		void update();
};

#endif
