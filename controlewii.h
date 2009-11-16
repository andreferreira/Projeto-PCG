#ifndef CONTROLEWII_H
#define CONTROLEWII_H

#include "controle.h"
#include <cwiid.h>

class ControleWii: public Controle {
	private:
	cwiid_wiimote_t *wiimote;	/* wiimote handle */
	struct cwiid_state state;	/* wiimote state */
	bdaddr_t bdaddr;	/* bluetooth device address */
	unsigned char mesg;
	unsigned char led_state;
	unsigned char rpt_mode;
	unsigned char rumble;
	public:
	ControleWii(Player &p);
	bool initializeWiimote();
	virtual void handleEvent(SDL_Event &e);
	virtual void handleOther();
};


#endif
