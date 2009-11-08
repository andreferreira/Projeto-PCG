#ifndef GRAVITY_H
#define GRAVITY_H

#include <set>
#include "geometry.h"
#include "thing.h"
#include "platform.h"

class GravityManager {
	private:
		std::set<Thing*> things;
		std::set<Platform*> platforms;
		bool checkGround(Thing* thing, Platform *platform);
	public:
		void subscribe(Thing* thing);
		void addPlatform(Platform* linha);
		void update();
};

#endif
