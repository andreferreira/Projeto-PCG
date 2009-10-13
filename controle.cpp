#include "controle.h"

Controle::Controle(Player p) {

}

void Controle::eventLoop() {
    while( SDL_PollEvent( &e ) )
        {
            switch( e.type )
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                //case SDL_KEYDOWN:
                    //switch (event.keysym.sym:
            }
        }
}

bool Controle::getQuit() {
    return quit;
}
