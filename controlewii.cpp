#include "controlewii.h"
#include "usereventtype.h"
#include <math.h>


ControleWii::ControleWii(Player &p) : Controle(p) {
	initializeWiimote();
	stickX = 0xffff;
	stickY = 0xffff;
	buttonsNunchuck = 0;
	buttonsWii = 0;
	game = jogador.game;
	for (int i = 0; i < CWIID_IR_SRC_COUNT; i++)
		cyclesSinceSeen[i] = -1;
}

void ControleWii::handleOther() {
	Uint8 *keystates = SDL_GetKeyState( NULL );
	if (keystates[SDLK_DOWN]) {
		jogador.onGround = false;
		jogador.bypass = true;
	}
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) { //botao esquerdo do mouse pressionado
		jogador.fire();
	}
	if (jogador.onGround && 
		buttonsNunchuck & 2) { //pulo com botao C ou para cima
		jogador.addSpeed( 0, -8);
		jogador.onGround = false;
	}

	if (buttonsNunchuck & 1) {//descer com botao Z ou para baixo
		jogador.onGround = false;
		jogador.bypass = true;
	}
	
	if (buttonsWii & 4) { //R atira
		jogador.fire();
	}

}

void ControleWii::handleEvent(SDL_Event &e) {
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
								/*y = y / sources;
								double angle = (y / 738.0) * PI;
								y = jogador.getY() + jogador.pescoco().y - jogador.game->camera.y - 100 * cos(angle);
								x = jogador.getX() + jogador.pescoco().x - jogador.game->camera.x + 100 * sin(angle);
								jogador.setAim(x,y);*/
								x = x / sources;
								y = y / sources;
								x = jogador.game->config->screen["width"] - (x / 1024.0) * jogador.game->config->screen["width"];
								y = (y / 738.0) * jogador.game->config->screen["height"];
								jogador.setAim(x+game->camera.x,y+game->camera.y);
							}
						}
						break;
						case CWIID_MESG_BTN: {
							//printf("Button Report: %.4X\n", mesg->btn_mesg.buttons);
							buttonsWii = mesg->btn_mesg.buttons;
							if (mesg->btn_mesg.buttons & 4) { //R atira
								jogador.fire();
							}
						}
						break;
						case CWIID_MESG_NUNCHUK: {
							int newX = mesg->nunchuk_mesg.stick[CWIID_X] - 120;
							int newY = mesg->nunchuk_mesg.stick[CWIID_Y] - 131;
							/*
							printf("Nunchuk Report: btns=%.2X stick=(%d,%d) acc.x=%d acc.y=%d "
								   "acc.z=%d\n", mesg->nunchuk_mesg.buttons,
								   newX,
								   newY,
								   mesg->nunchuk_mesg.acc[CWIID_X],
								   mesg->nunchuk_mesg.acc[CWIID_Y],
								   mesg->nunchuk_mesg.acc[CWIID_Z]);*/

							if (stickX != 0xffff) { //para calibrar
								//jogador.addSpeed(-3.0*stickX/128,0);
								jogador.setSpeed(3.0*newX/128,jogador.getSpeedY());
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

							if (newY < -60 || (mesg->nunchuk_mesg.buttons & 1)) {//descer com botao Z ou para baixo
								jogador.onGround = false;
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
				jogador.setAim(e.motion.x+game->camera.x,e.motion.y+game->camera.y);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			jogador.fire();
		break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					jogador.addSpeed(3,0);
					break;
				case SDLK_RIGHT:
					jogador.addSpeed(-3,0);
					break;
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
				case SDLK_LEFT:
					jogador.addSpeed(-3,  0);
					break;
				case SDLK_RIGHT:
					jogador.addSpeed( 3,  0);
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
void err(cwiid_wiimote_t *wiimote, const char *s, va_list ap)
{
	if (wiimote) printf("%d:", cwiid_get_id(wiimote));
	else printf("-1:");
	vprintf(s, ap);
	printf("\n");
}

void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
                    union cwiid_mesg mesg[], struct timespec *timestamp)
{
	int i, j;
	int valid_source;



	for (i=0; i < mesg_count; i++)
	{
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
		/*switch (mesg[i].type) {
		case CWIID_MESG_STATUS:
			printf("Status Report: battery=%d extension=",
			       mesg[i].status_mesg.battery);
			switch (mesg[i].status_mesg.ext_type) {
			case CWIID_EXT_NONE:
				printf("none");
				break;
			case CWIID_EXT_NUNCHUK:
				printf("Nunchuk");
				break;
			case CWIID_EXT_CLASSIC:
				printf("Classic Controller");
				break;
			default:
				printf("Unknown Extension");
				break;
			}
			printf("\n");
			break;
		case CWIID_MESG_BTN:
			printf("Button Report: %.4X\n", mesg[i].btn_mesg.buttons);
			break;
		case CWIID_MESG_ACC:
			printf("Acc Report: x=%d, y=%d, z=%d\n",
                   mesg[i].acc_mesg.acc[CWIID_X],
			       mesg[i].acc_mesg.acc[CWIID_Y],
			       mesg[i].acc_mesg.acc[CWIID_Z]);
			break;
		case CWIID_MESG_IR:
			printf("IR Report: ");
			valid_source = 0;
			for (j = 0; j < CWIID_IR_SRC_COUNT; j++) {
				if (mesg[i].ir_mesg.src[j].valid) {
					valid_source = 1;
					printf("(%d,%d) ", mesg[i].ir_mesg.src[j].pos[CWIID_X],
					                   mesg[i].ir_mesg.src[j].pos[CWIID_Y]);
				}
			}
			if (!valid_source) {
				printf("no sources detected");
			}
			printf("\n");
			break;
		case CWIID_MESG_NUNCHUK: {
			printf("Nunchuk Report: btns=%.2X stick=(%d,%d) acc.x=%d acc.y=%d "
			       "acc.z=%d\n", mesg[i].nunchuk_mesg.buttons,
			       mesg[i].nunchuk_mesg.stick[CWIID_X],
			       mesg[i].nunchuk_mesg.stick[CWIID_Y],
			       mesg[i].nunchuk_mesg.acc[CWIID_X],
			       mesg[i].nunchuk_mesg.acc[CWIID_Y],
			       mesg[i].nunchuk_mesg.acc[CWIID_Z]);
			break;
		}
		case CWIID_MESG_CLASSIC:
			printf("Classic Report: btns=%.4X l_stick=(%d,%d) r_stick=(%d,%d) "
			       "l=%d r=%d\n", mesg[i].classic_mesg.buttons,
			       mesg[i].classic_mesg.l_stick[CWIID_X],
			       mesg[i].classic_mesg.l_stick[CWIID_Y],
			       mesg[i].classic_mesg.r_stick[CWIID_X],
			       mesg[i].classic_mesg.r_stick[CWIID_Y],
			       mesg[i].classic_mesg.l, mesg[i].classic_mesg.r);
			break;
		case CWIID_MESG_ERROR:
			if (cwiid_close(wiimote)) {
				fprintf(stderr, "Error on wiimote disconnect\n");
				exit(-1);
			}
			exit(0);
			break;
		default:
			printf("Unknown Report");
			break;
		}*/
	}
}

void set_led_state(cwiid_wiimote_t *wiimote, unsigned char led_state)
{
	if (cwiid_set_led(wiimote, led_state)) {
		fprintf(stderr, "Error setting LEDs \n");
	}
}
	
void set_rpt_mode(cwiid_wiimote_t *wiimote, unsigned char rpt_mode)
{
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
	//set_rpt_mode(wiimote, rpt_mode);
	
	toggle_bit(rpt_mode, CWIID_RPT_NUNCHUK); //abilita status report de nunchuck
	//set_rpt_mode(wiimote, rpt_mode);
	
	toggle_bit(led_state, CWIID_LED4_ON); //liga quarto LED para indentificar ligaçao com o NOSSO jogo e nao o wii
	set_led_state(wiimote, led_state);
	
	toggle_bit(rpt_mode, CWIID_RPT_IR); //abilita recebimento do infravermelho
	set_rpt_mode(wiimote, rpt_mode);
	
	if (cwiid_enable(wiimote, CWIID_FLAG_MESG_IFC)) {
		fprintf(stderr, "Error enabling messages\n");
		return false;
	}
	
}
