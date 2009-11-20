#include "controle.h"
#include "usereventtype.h"

Controle::Controle(Player &p) : jogador( p )  {
    quit = false;
}

void Controle::handleEvents() {
	SDL_Event e;	
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
						jogador.equip(jogador.game->weaponManager->getWeapon("Shotgun"));
						break;
					case SDLK_F4:
						jogador.equip(jogador.game->weaponManager->getWeapon("Flamethrower"));
						break;
					case SDLK_F5:
						jogador.game->reloadLua();
						break;
					case SDLK_F6:
						jogador.setPosition(jogador.game->getSpawn().x,jogador.game->getSpawn().y);
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
