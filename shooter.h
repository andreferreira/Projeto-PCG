#ifndef SHOOTER_H
#define SHOOTER_H

#include "game.h"
#include "geometry.h"
#include "thing.h"
#include "weapon.h"

class Game;
class Player;

class Shooter: public Thing {
	protected:
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
		Game* game;
        Shooter(Game* agame, Ponto pos, Ponto speed);
        void desenha();
		void setAim(double x, double y);
		void equip(Weapon* aweapon);
		virtual Linha getBaseLine();
};

#endif
