#include "weaponitem.h"

WeaponItem::WeaponItem(Weapon *a, Polygon c): arma(a), collision(c) {
	setSpeed(0, 0);
	maxspeed.x = 5;
	maxspeed.y = 20;
}

Polygon WeaponItem::getCollision() {
	return collision;
}

void WeaponItem::desenha() {
	glPushMatrix();
		glTranslatef(posicao.x, posicao.y, 0);
		arma->desenha();
	glPopMatrix();
}

Linha WeaponItem::getBaseLine() {
	return collision.linhas[2]; // minX, minY, maxX, minY
}
