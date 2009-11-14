#ifndef CONTROLETECLADO_H
#define CONTROLETECLADO_H

#include "controle.h"

class ControleTeclado: public Controle {
	public:
		ControleTeclado(Player &p);
		virtual void handleEvent(SDL_Event &e);
		virtual void handleOther();
};

#endif
