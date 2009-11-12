#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "geometry.h"
#include "thing.h"
#include "luaenv.h"

class Weapon: public Thing {
	private:
		Ponto leftHand;
		Ponto rightHand;
	public:
		Polygon sprite;
		std::string name;
		void setSprite(Polygon asprite) { sprite = asprite;}
		void setLeftHand(Ponto hand) {leftHand = hand;}
		void setRightHand(Ponto hand) {rightHand = hand;}
		Ponto getLeftHand() {return leftHand;}
		Ponto getRightHand(){return rightHand;}
		void desenha();
};


#endif
