#include "controle.h"

Controle::Controle(Player &p) : jogador( p )  {
    quit = false;
}

void Controle::handleEvents() {
	SDL_Event e;	
    while( SDL_PollEvent( &e ) ) {
        switch( e.type ) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    default: handleEvent(e);break;
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
					case SDLK_F5:
						jogador.game->reloadLua();
						break;
					case SDLK_F6:
						jogador.setPosition(jogador.game->getSpawn().x,jogador.game->getSpawn().y);
						break;
                    default: handleEvent(e);break;
                }
                break;
			default:
				handleEvent(e);
				break;
        }
    }
	Uint8 *keystates = SDL_GetKeyState( NULL );
	if (keystates[SDLK_DOWN]) {
		jogador.onGround = false;
		jogador.bypass = true;
	}
	
}
