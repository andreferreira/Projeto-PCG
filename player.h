#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "shooter.h"

class Player: public Shooter {
	public:
        Player(Game* agame, Ponto pos, Ponto speed);
		void desenha();
};

#endif
