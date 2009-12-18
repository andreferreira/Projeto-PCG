#ifndef PLAYER_H
#define PLAYER_H
#define MAXHP 100

#include "game.h"
#include "shooter.h"

class Player: public Shooter {
	public:
        Player(Game* agame, Ponto pos, Ponto speed);
		void desenha();
		virtual void collide(Thing* b);
		int hp;
};

#endif
