#include "player.h"
#include "shot.h"

Player::Player(Game* agame, Ponto pos, Ponto speed): Shooter(agame, pos, speed) { }

void Player::desenha() {
	game->desenhaMira(aim);
    Shooter::desenha();
}

#include <iostream>

void Player::collide(Thing *b) {
	Shot* shot = dynamic_cast<Shot*>(b);
	if (shot) {
		shot->dead = true;
		std::cout<<"I have been shot"<<std::endl;
	}
}
