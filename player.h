#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "geometry.h"
#include "thing.h"
#include "weapon.h"

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
		Ponto aim;
		Weapon* weapon;
		double tamanhoAntebraco();
		double tamanhoBraco();
		double getAngle();
		Ponto getCotovelo(Ponto ombro, Ponto hand);
	public:
        Player(Game* agame);
        void desenha();
		void setAim(double x, double y);
		void equip(Weapon* aweapon);
		virtual Linha getBaseLine();
};

#endif
