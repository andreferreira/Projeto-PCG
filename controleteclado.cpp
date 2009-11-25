#include "controleteclado.h"

ControleTeclado::ControleTeclado(Player &p) : Controle(p) {
	
}

void ControleTeclado::handleOther() {
	Uint8 *keystates = SDL_GetKeyState( NULL );

	if (keystates[SDLK_DOWN]) {
		jogador.onGround = false;
		jogador.bypass = true;
	}
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) { //botao esquerdo do mouse pressionado
		jogador.fire();
	}
}

void ControleTeclado::handleEvent(SDL_Event &e) {
	switch( e.type ) {
		case SDL_MOUSEMOTION: {
				jogador.setAim(e.motion.x+game->camera.x,e.motion.y+game->camera.y);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			jogador.fire();
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
				case SDLK_DOWN:
					jogador.onGround = false;
					jogador.bypass = true;
					break;
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
