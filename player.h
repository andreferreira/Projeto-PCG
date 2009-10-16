#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "geometry.h"
#include "thing.h"

class Game;

class Player: public Thing {
	private:
		Game* game;
		Ponto leftFeet();
		Ponto rightFeet();
	public:
        Player(Game* agame);
        void desenha();
		virtual Rect getBaseRect();
};

#endif
