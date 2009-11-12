#include "player.h"

Player::Player(Game* agame): Shooter(agame, Ponto(40, 40), Ponto(0, 0)) { }

void Player::desenha() {
	game->desenhaMira(aim);
    Shooter::desenha();
}