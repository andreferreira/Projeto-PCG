#include "controle.h"

Controle::Controle(Player &p) : jogador( p )  {
    
}

void Controle::eventLoop() {
    while( SDL_PollEvent( &e ) ) {
        switch( e.type ) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        jogador.addSpeed(0,1);
                        break;
                    case SDLK_DOWN:
                        jogador.addSpeed(0,-1);
                        break;
                    case SDLK_LEFT:
                        jogador.addSpeed(1,0);
                        break;
                    case SDLK_RIGHT:
                        jogador.addSpeed(-1,0);
                        break;
                    default: break;
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        jogador.addSpeed( 0, -1);
                        break;
                    case SDLK_DOWN:
                        jogador.addSpeed( 0,  1);
                        break;
                    case SDLK_LEFT:
                        jogador.addSpeed(-1,  0);
                        break;
                    case SDLK_RIGHT:
                        jogador.addSpeed( 1,  0);
                        break;
                    default: break;
                }
                break;
        }
    }
}

bool Controle::getQuit() {
    return quit;
}

Player& Controle::getJogador() {
    return jogador;
}
