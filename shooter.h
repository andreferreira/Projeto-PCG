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
		Ponto aim;
		Ponto realRightfeet;
		Ponto realLeftfeet;
		Ponto imaginaryRightfeet(int t);
		Ponto imaginaryLeftfeet(int t);
		Weapon* weapon;
		double tamanhoAntebraco();
		double tamanhoBraco();
		double tamanhoCoxa();
		double tamanhoPerna();
		double getAngle();
		Ponto getJunta(Ponto superior, Ponto inferior,
						double tamanhoSuperior, double tamanhoInferior);
		bool canfire;
	public:
		Ponto pescoco();
		Game* game;
        Shooter(Game* agame, Ponto pos, Ponto speed);
        void desenha();
		void setAim(double x, double y);
		void equip(Weapon* aweapon);
		void fire();
		void allowFire();
		void animate();
		virtual Linha getBaseLine();
		virtual Polygon getCollision();
};

#endif
