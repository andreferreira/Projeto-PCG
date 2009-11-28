#include "weaponitem.h"

WeaponItem::WeaponItem(Weapon *a, Polygon c): arma(a), collision(c) {
	setSpeed(0, 0);
	maxspeed.x = 5;
	maxspeed.y = 20;
	bypass = false;
	onGround = false;
}

Polygon WeaponItem::getCollision() {
	return collision;
}

void WeaponItem::desenha() {
	glPushMatrix();
		glTranslatef(posicao.x, posicao.y, 0);
		//glRotatef(180, 0, 0, -1);
		arma->desenha();
	glPopMatrix();
}

Linha WeaponItem::getBaseLine() {
	return collision.linhas[2]; // minX, minY, maxX, minY
}

void WeaponItem::collide(Thing* b) {
	//static int i = 0;
	//std::cout << "lol " << i++ << std::endl;
}
