#ifndef WEAPONITEM_H
#define WEAPONITEM_H

#include "weapon.h"
#include "thing.h"
#include "geometry.h"

// gerar superclasse Item no futuro?
class WeaponItem: public Thing {
	private:
		Weapon *arma;
		Polygon collision;
	public:
		WeaponItem(Weapon *a, Polygon c);
		virtual Linha getBaseLine();
		virtual Polygon getCollision();
		virtual void collide(Thing* b);
		void desenha();
};

#endif
