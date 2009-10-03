#include "plataformas.h"
#include <time.h>
const int variaX = 200;
const int variaY = 200;

std::vector<Linha> geraMapa(int n) {
	srand(time(NULL));
	std::vector<Linha> mapa;
	for (int i = 0; i < n; i++) {
		int posX1 = rand() % (640 - variaX);
		int posX2 = posX1 + (rand() % variaX);
		int posY1 = rand() % (480 - variaY/2);
		int posY2 = posY1 + (rand() % variaY) - variaY/2;
		Linha nova(posX1,posY1,posX2,posY2);
		mapa.push_back(nova);
	}
	return mapa;
}
