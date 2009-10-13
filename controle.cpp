#include "controle.h"

Controle::Controle(Player &p) : jogador( p )  {
    
}

void Controle::eventLoop() {
    while( SDL_PollEvent( &e ) ) {
        switch( e.type ) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        jogador.move( 0, -1);
                        break;
                    case SDLK_DOWN:
                        jogador.move( 0,  1);
                        break;
                    case SDLK_LEFT:
                        jogador.move(-1,  0);
                        break;
                    case SDLK_RIGHT:
                        jogador.move( 1,  0);
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
