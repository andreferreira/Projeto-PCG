#ifndef CONTROLE_H
#define CONTROLE_H

#include "player.h"

class Controle {
    private:
        Player &jogador;
        SDL_Event e;
        bool quit;
    public:
        Controle(Player &p) ;
        void eventLoop();
        bool getQuit();
};

#endif
