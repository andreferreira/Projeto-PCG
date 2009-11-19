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

void ShotManager::move(int t) {
	std::vector<Shot*>::iterator it;
	for (it = shots.begin(); it != shots.end(); it++) {
		(*it)->move(t);
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

void ShotManager::clearShots() {
	shots.clear();
}
