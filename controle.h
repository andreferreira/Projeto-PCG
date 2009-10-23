#ifndef CONTROLE_H
#define CONTROLE_H

#include "player.h"

class Controle {
    protected:
        Player &jogador;
        SDL_Event e;
        bool quit;
        bool passing;
    public:
        Controle(Player &p);
        virtual void eventLoop() = 0;
        bool getQuit() {return quit;};
        bool isPassing() {return passing;};
};

#endif
