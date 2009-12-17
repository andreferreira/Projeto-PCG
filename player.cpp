#include "player.h"
#include "shot.h"

Player::Player(Game* agame, Ponto pos, Ponto speed): Shooter(agame, pos, speed) { 
	hp = 1000;
}

void Player::desenha() {
	game->desenhaMira(aim);
    Shooter::desenha();
}

void Player::collide(Thing *b) {
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot && shot->firedBy != this) {
		shot->dead = true;
		if (this->getPosition().x < shot->firedBy->getPosition().x)
			addToAngle -= 0.5;
		else
			addToAngle += 0.5;
		addToAngle = std::max(std::min(addToAngle, PI/2),-PI/2);
	}
}
