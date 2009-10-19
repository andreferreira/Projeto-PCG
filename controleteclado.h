#ifndef CONTROLETECLADO_H
#define CONTROLETECLADO_H

#include "controle.h"

class ControleTeclado: public Controle {
	private:
		SDL_Event e;
	public:
		ControleTeclado(Player &p);
		virtual void eventLoop();
};

#endif
