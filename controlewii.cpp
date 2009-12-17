#include "controlewii.h"
#include "usereventtype.h"
#include "weaponitem.h"
#include <cmath>

ControleWii::ControleWii(Player &p) : Controle(p) {
	connected = false;
	initializeWiimote();
	stickX = 0xffff;
	stickY = 0xffff;
	buttonsNunchuck = 0;
	buttonsWii = 0;
	for (int i = 0; i < CWIID_IR_SRC_COUNT; i++)
		cyclesSinceSeen[i] = -1;
}

void ControleWii::handleOther() {
	if (jogador.dead) return;
	jogador.crawl = false;
	Uint8 *keystates = SDL_GetKeyState( NULL );
	if (keystates[SDLK_DOWN]) {
		jogador.bypass = true;
	}
	if (jogador.onGround && keystates[SDLK_RCTRL]) {
		jogador.crawl = true;
	}
	if (keystates[SDLK_LEFT]) {
		jogador.addSpeed(-3,  0);
	}
	if (keystates[SDLK_RIGHT]) {
		jogador.addSpeed(3,  0);
	}
	if (keystates[SDLK_RIGHT]) {
		jogador.addSpeed(3,  0);
	}
	if (!keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT])
		jogador.addSpeed(closerToZero(-jogador.getSpeedX(),sign(jogador.getSpeedX())*-0.5),0);
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) { //botao esquerdo do mouse pressionado
		jogador.fire();
	}
	if (jogador.onGround && 
		buttonsNunchuck & 2) { //pulo com botao C ou para cima
		jogador.addSpeed( 0, -8);
		jogador.onGround = false;
	}
	if (jogador.onGround && buttonsNunchuck & 1) {//deitar com z
		jogador.crawl = true;
	}
	
	if (buttonsWii & 4) { //R atira
		jogador.fire();
	}

}

void ControleWii::handleEvent(SDL_Event &e) {
	if (jogador.dead) return;
	std::list<WeaponItem*>::iterator it;
	bool pegou = false;
	switch( e.type ) {
		case SDL_USEREVENT:
			switch (e.user.code) {
				case WIIMOTEEVENT:
					cwiid_mesg_type* type = (cwiid_mesg_type*)e.user.data1;
					union cwiid_mesg *mesg = (union cwiid_mesg*)e.user.data2;
					switch (*type) {
						case CWIID_MESG_IR: {
							int sources = 0;
							double x = 0.0;
							double y = 0.0;
							for (int j = 0; j < CWIID_IR_SRC_COUNT; j++) {
								if (cyclesSinceSeen[j] != -1)
									cyclesSinceSeen[j]++;
								if (mesg->ir_mesg.src[j].valid) {
									cyclesSinceSeen[j] = 0;
									lastSeenAt[j].x = mesg->ir_mesg.src[j].pos[CWIID_X];
									lastSeenAt[j].y = mesg->ir_mesg.src[j].pos[CWIID_Y];
								}
							}
							for (int i = 0; i < CWIID_IR_SRC_COUNT; i++)
								if (cyclesSinceSeen[i] != -1) {
									x += lastSeenAt[i].x;
									y += lastSeenAt[i].y;
									sources++;
								}
							if (sources > 0) {
								x = x / sources;
								y = y / sources;
								x = jogador.game->config->screen["width"] - (x / 1024.0) * jogador.game->config->screen["width"];
								y = (y / 738.0) * jogador.game->config->screen["height"];
								jogador.setAim(x+game->camera.x,y+game->camera.y);
							}
						}
						break;
						case CWIID_MESG_BTN: {
							buttonsWii = mesg->btn_mesg.buttons;
							if (mesg->btn_mesg.buttons & 4) { //R atira
								jogador.fire();
							}
						}
						break;
						case CWIID_MESG_NUNCHUK: {
							int newX = mesg->nunchuk_mesg.stick[CWIID_X] - 120;
							int newY = mesg->nunchuk_mesg.stick[CWIID_Y] - 131;

							if (stickX != 0xffff) {
								jogador.setSpeed(4.0*newX/128,jogador.getSpeedY());
							}
							stickX = newX;
							stickY = newY;
							buttonsNunchuck = mesg->nunchuk_mesg.buttons;
							
							if (jogador.onGround && 
								((mesg->nunchuk_mesg.buttons & 2) ||
								 newY > 60)) { //pulo com botao C ou para cima
								jogador.addSpeed( 0, -8);
								jogador.onGround = false;
							}

							if (newY < -60) {// || (mesg->nunchuk_mesg.buttons & 1)) {//descer com botao Z ou para baixo
								jogador.bypass = true;
							}
						}
						break;
					
					}
					free(e.user.data1);
					free(e.user.data2);
				break;
			}
		break;
		case SDL_MOUSEMOTION: {
			if (!connected)
				jogador.setAim(e.motion.x+game->camera.x,e.motion.y+game->camera.y);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			jogador.fire();
		break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
				default: break;
			}
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_DOWN:
					jogador.onGround = false;
					jogador.bypass = true;
					break;
				case SDLK_UP:
					if (jogador.onGround) {
						jogador.addSpeed( 0, -8);
						jogador.onGround = false;
					}
					break;
				case SDLK_RETURN:
					for (it = map->items.begin(); it != map->items.end(); ++it)
						if (game->collisionManager->checkCollision(&jogador, (Thing*) *it)) {
							jogador.equip((*it)->getWeapon());
							pegou = true;
							break;
						}
					if (pegou)
						map->items.erase(it);
					break;
				default: break;
			}
			break;
	}
}

#define toggle_bit(bf,b)	\
	(bf) = ((bf) & b)		\
	       ? ((bf) & ~(b))	\
	       : ((bf) | (b))

cwiid_err_t err;
void err(cwiid_wiimote_t *wiimote, const char *s, va_list ap) {
	if (wiimote) printf("%d:", cwiid_get_id(wiimote));
	else printf("-1:");
	vprintf(s, ap);
	printf("\n");
}

void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
                    union cwiid_mesg mesg[], struct timespec *timestamp) {
	int i, j;
	int valid_source;

	for (i=0; i < mesg_count; i++) {
		SDL_Event event;
		SDL_UserEvent userevent;
		userevent.type = SDL_USEREVENT;	
		event.type = SDL_USEREVENT;
		userevent.code = WIIMOTEEVENT;
		cwiid_mesg_type *type = (cwiid_mesg_type*)malloc(sizeof(cwiid_mesg_type));
		*type =  mesg[i].type;
		userevent.data1 = (void*)type;
		union cwiid_mesg *m = (union cwiid_mesg *)malloc(sizeof(union cwiid_mesg));
		*m = mesg[i];
		userevent.data2 = m;
		event.user = userevent;
		SDL_PushEvent(&event);
	}
}

void set_led_state(cwiid_wiimote_t *wiimote, unsigned char led_state) {
	if (cwiid_set_led(wiimote, led_state)) {
		fprintf(stderr, "Error setting LEDs \n");
	}
}
	
void set_rpt_mode(cwiid_wiimote_t *wiimote, unsigned char rpt_mode) {
	if (cwiid_set_rpt_mode(wiimote, rpt_mode)) {
		fprintf(stderr, "Error setting report mode\n");
	}
}

bool ControleWii::ControleWii::initializeWiimote() {
	mesg = 0;
	led_state = 0;
	rpt_mode = 0;
	rumble = 0;

	cwiid_set_err(err);

	bdaddr = *BDADDR_ANY;

	/* Connect to the wiimote */
	printf("Put Wiimote in discoverable mode now (press 1+2)...\n");
	if (!(wiimote = cwiid_open(&bdaddr, 0))) {
		fprintf(stderr, "Unable to connect to wiimote\n");
		return false;
	}
	if (cwiid_set_mesg_callback(wiimote, cwiid_callback)) {
		fprintf(stderr, "Unable to set message callback\n");
		return false;
	}
	
	toggle_bit(rpt_mode, CWIID_RPT_BTN); //abilita status report de botoes
	
	toggle_bit(rpt_mode, CWIID_RPT_NUNCHUK); //abilita status report de nunchuck
	
	toggle_bit(led_state, CWIID_LED4_ON); //liga quarto LED para indentificar ligaçao com o NOSSO jogo e nao o wii
	set_led_state(wiimote, led_state);
	
	toggle_bit(rpt_mode, CWIID_RPT_IR); //abilita recebimento do infravermelho
	set_rpt_mode(wiimote, rpt_mode);
	
	if (cwiid_enable(wiimote, CWIID_FLAG_MESG_IFC)) {
		fprintf(stderr, "Error enabling messages\n");
		return false;
	}
	connected = true;
	return true;
}
