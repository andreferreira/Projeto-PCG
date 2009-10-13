#ifndef PLAYER_H
#define PLAYER_H

#include "geometry.h"

class Player {
	private:
		Ponto posicao;
		Vetor velocidade;
	public:
        Player(int x, int y);
		void desenha();
};

#endif
