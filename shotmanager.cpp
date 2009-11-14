#include "shotmanager.h"
#include "shot.h"

void ShotManager::addShot(Shot* shot) {
	shots.push_back(shot);
}

void ShotManager::desenha() {
	std::vector<Shot*>::iterator it;
	for (it = shots.begin(); it != shots.end(); it++) {
		(*it)->desenha();
	}
}

void ShotManager::move() {
	std::vector<Shot*>::iterator it;
	for (it = shots.begin(); it != shots.end(); it++) {
		(*it)->move();
	}
}

void ShotManager::deleteShot(Shot* shot) {
	std::vector<Shot*>::iterator it;
	for (it = shots.begin(); it != shots.end(); it++) {
		if (*it == shot) {
			shots.erase(it);
			return;
		}
	}
}
