#include "game.h"
#include "configmanager.h"

int main() {
	ConfigManager config;
	config.load();
	Game agame(&config);
	agame.mainLoop();
}
