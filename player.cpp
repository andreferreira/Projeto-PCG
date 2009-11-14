#include "player.h"

Player::Player(Game* agame, Ponto pos, Ponto speed): Shooter(agame, pos, speed) { }

void Player::desenha() {
	game->desenhaMira(aim);
    Shooter::desenha();
}
