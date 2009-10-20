#ifndef WEAPON_H
#define WEAPON_H

#include "geometry.h"
#include "thing.h"

class Weapon: public Thing {
	private:
		Polygon sprite;
		Ponto leftHand;
		Ponto rightHand;
	public:
		void setSprite(Polygon asprite) { sprite = asprite;}
		void setLeftHand(Ponto hand) {leftHand = hand;}
		void setRightHand(Ponto hand) {rightHand = hand;}
		Ponto getLeftHand() {return leftHand;}
		Ponto getRightHand(){return rightHand;}
		void desenha();
};


#endif
