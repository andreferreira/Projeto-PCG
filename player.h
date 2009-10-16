#ifndef PLAYER_H
#define PLAYER_H

#define CINTURA 0,-30
#define PESCOCO 0,-60

#include "game.h"
#include "geometry.h"
#include "thing.h"

class Game;

class Player: public Thing {
	private:
		Game* game;
		Ponto leftFeet();
		Ponto rightFeet();
		Ponto body();
		Ponto leftArm();
		Ponto rightArm();
	public:
        Player(Game* agame);
        void desenha();
		virtual Rect getBaseRect();
};

#endif
