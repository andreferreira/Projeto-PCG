#include "gravity.h"

void GravityManager::subscribe(Thing* thing) {
	things.insert(thing);
}

void GravityManager::addPlataform(Linha* linha) {
	plataforms.insert(linha);
}

void GravityManager::update() {
	std::set<Thing*>::iterator it;
	for (it = things.begin(); it != things.end(); it++) {
		checkGround(*it);
	}
}

void GravityManager::checkGround(Thing* thing) {
	
	
}
