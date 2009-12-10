#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "geometry.h"
#include "thing.h"
#include "luaenv.h"

class Game;
class Shooter;

class Weapon {
	private:
		Ponto leftHand;
		Ponto rightHand;
		Ponto tip;
		lua_State* lstate;
	public:
		Ponto position; //POSICAO USADA SOMENTE QUANDO ATIRADA, NAO USAR PARA OUTRAS COISAS
		Shooter* firedBy; //MESMA COISA
		Game *game;
		Weapon (Game* g,lua_State* l) {game = g; lstate = l;}
		Polygon sprite;
		int fireRate;
		std::string name;
		void setSprite(Polygon asprite) { sprite = asprite;}
		void setLeftHand(Ponto hand) {leftHand = hand;}
		void setRightHand(Ponto hand) {rightHand = hand;}
		Ponto getLeftHand() {return leftHand;}
		Ponto getRightHand(){return rightHand;}
		void desenha();
		void setTip(Ponto t) {tip = t;}
		Ponto getTip() {return tip;}
		void fire(Ponto place, double angle, Shooter *_firedBy);
};


#endif
