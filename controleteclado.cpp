#include "controleteclado.h"

ControleTeclado::ControleTeclado(Player &p) : Controle(p) {
	
}

void ControleTeclado::handleEvent(SDL_Event &e) {
	switch( e.type ) {
		case SDL_MOUSEMOTION: {
				jogador.setAim(e.motion.x,e.motion.y);
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					jogador.addSpeed(3,0);
					break;
				case SDLK_RIGHT:
					jogador.addSpeed(-3,0);
					break;
				default: break;
			}
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					if (jogador.onGround) {
						jogador.addSpeed( 0, -8);
						jogador.onGround = false;
					}
					break;
				case SDLK_LEFT:
					jogador.addSpeed(-3,  0);
					break;
				case SDLK_RIGHT:
					jogador.addSpeed( 3,  0);
					break;
				default: break;
			}
			break;
	}
}
