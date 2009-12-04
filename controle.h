#ifndef CONTROLE_H
#define CONTROLE_H

#include "player.h"

class Controle {
    protected:
        Player &jogador;
        bool quit;
		Game* game;
		Mapa* map;
    public:
        Controle(Player &p);
        void handleEvents();
		virtual void handleEvent(SDL_Event &e) = 0;
		virtual void handleOther() = 0;
        bool getQuit() {return quit;};
};

#endif
