#include "controle.h"
#include "usereventtype.h"

Controle::Controle(Player &p) : jogador( p )  {
    quit = false;
	game = jogador.game;
	map = game->mapa;
}

void Controle::handleEvents() {
	SDL_Event e;
	jogador.bypass = false;
    while( SDL_PollEvent( &e ) ) {
        switch( e.type ) {
			case SDL_USEREVENT:
				switch (e.user.code) {
					case FUNCTIONCALL:{
						void (*p) (void*) = (void (*)(void*))e.user.data1;
						p(e.user.data2);
					}
					break;
					default: handleEvent(e); break;
				}
				break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
					case SDLK_F3:
						jogador.equip(game->weaponManager->getWeapon("Shotgun"));
						break;
					case SDLK_F4:
						jogador.equip(game->weaponManager->getWeapon("Flamethrower"));
						break;
					case SDLK_F5:
						game->reloadLua();
						break;
					case SDLK_F6:
						jogador.setPosition(game->getSpawn().x, game->getSpawn().y);
						break;
                    default: handleEvent(e);break;
                }
                break;
			case SDL_VIDEORESIZE:
				jogador.game->resize(e.resize.w, e.resize.h);
				break;
			default:
				handleEvent(e);
				break;
        }
    }
	handleOther();
}
