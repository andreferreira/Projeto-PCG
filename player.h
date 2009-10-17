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
		Ponto cintura();
		Ponto leftArm();
		Ponto rightArm();
        Ponto pescoco();
	public:
        Player(Game* agame);
        void desenha();
		virtual Linha getBaseLine();
};

#endif
