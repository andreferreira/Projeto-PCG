#include "controle.h"

Controle::Controle(Player &p) : jogador( p )  {
    quit = false;
}

bool Controle::getQuit() {
    return quit;
}
