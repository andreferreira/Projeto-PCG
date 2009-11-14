#ifndef SHOTMANAGER_H
#define SHOTMANAGER_H

#include <vector>

class Shot;

class ShotManager {
	private:
		std::vector<Shot*> shots;
	public:
		void addShot(Shot* shot);
		void desenha();
		void move();
		void deleteShot(Shot* shot);
};

#endif
