#include <math.h>
#include "shooter.h"
#include "gravity.h"
#include "shot.h"
#include "shotmanager.h"
#include "usereventtype.h"


Shooter::Shooter(Game* agame, Ponto pos, Ponto speed) {
	weapon = NULL;
    setPosition(pos.x, pos.y);
    setSpeed(speed.x, speed.y);
	game = agame;
	game->gravityManager->subscribe(this);
	maxspeed.x = 5;
	maxspeed.y = 20;
	canfire = true;
}

void Shooter::equip(Weapon* aweapon) {
	//desequipar a anterior aqui mais tarde
	weapon = aweapon;
}

static void allowFireFunc(void* param) {
	((Shooter*)param)->allowFire();
}

static Uint32 allowFireCallback(Uint32 interval, void *param) {
	SDL_Event event;
	SDL_UserEvent userevent;
	userevent.type = SDL_USEREVENT;
	userevent.code = FUNCTIONCALL;
	userevent.data1 = (void*)allowFireFunc;
	userevent.data2 = (void*)param;
	
	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);

	return 0;
}

void Shooter::allowFire() {
	canfire = true;
}



void Shooter::fire() {
	if (!canfire || weapon == NULL)
		return;
	SDL_AddTimer(weapon->fireRate*game->rate,allowFireCallback,this);
	canfire = false;
	Ponto tiplinha = weapon->getTip();
	double angle = getAngle();
	double cosAngle = cos(angle);
	double sinAngle = sin(angle);
	Ponto tip;
	tip.x = (cosAngle*tiplinha.x+sinAngle*tiplinha.y);
	tip.y = -(sinAngle*tiplinha.x-cosAngle*tiplinha.y);
	tip = tip + pescoco() + getPosition();
	
	weapon->fire(tip,angle);
}


Ponto Shooter::leftFeet() {
	Ponto pe(-10,0);
	return pe;
}

Ponto Shooter::rightFeet() {
	Ponto pe(10,0);
	return pe;
}

Ponto Shooter::leftArm() {
	if (weapon == NULL) {
		Ponto braco(-10,-30);
		return braco;
	}
	else
		return weapon->getLeftHand();
}

Ponto Shooter::rightArm() {
	if (weapon == NULL) {
		Ponto braco(10,-30);
		return braco;
	}
	else
		return weapon->getRightHand();
}

Ponto Shooter::cintura() {
    Ponto c(0,-30);
    return c;
}

Ponto Shooter::pescoco() {
   Ponto neck(0,-60);
   return neck;
}

double areaTriangle(double a, double b, double c) {
	if (a < b) std::swap(a,b);
	if (a < c) std::swap(a,c);
	if (b < c) std::swap(b,c);
	//a >= b >= c
	
	return sqrt((a+(b+c))*(c-(a-b))*(c+(a-b))*(a+(b-c)))/4.0;	
}

//retorna cotovelo em relacao ao ombro, usa matematica levemente pesada, cuidado ao mexer
Ponto Shooter::getJunta(Ponto superior, Ponto inferior, 
						double tamanhoSuperior, double tamanhoInferior) {
	double a = tamanhoSuperior;
	double b = tamanhoInferior;
	double d = distance(superior,inferior);
	double area = areaTriangle(a,b,d);
	double ylinha = 2.0*area/d;
	double xlinha = sqrt(a*a-ylinha*ylinha);
	double sinTheta = (inferior.y-superior.y)/d;
	double cosTheta = (inferior.x-superior.x)/d;
	Ponto ret;
	ret.x = (cosTheta*xlinha-sinTheta*ylinha);
	ret.y = (sinTheta*xlinha+cosTheta*ylinha);
	return ret;
}

//cuidado, distancia da arma nao pode exceder tamanhoBraco+tamanhoAntebraco
double Shooter::tamanhoBraco() {
	return 20.0;
}

double Shooter::tamanhoAntebraco() {
	return 13.0;
}

double Shooter::getAngle() {
	Ponto gameneck = pescoco() + getPosition();
	double hyp = sqrt((aim.x-gameneck.x)*(aim.x-gameneck.x) + 
					  (aim.y-gameneck.y)*(aim.y-gameneck.y));
	if (aim.y <= gameneck.y)
		return -acos((-aim.x+gameneck.x)/hyp);
	else
		return acos((-aim.x+gameneck.x)/hyp);
}

void Shooter::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		Ponto leftfeet = leftFeet();
		Ponto rightfeet = rightFeet();
		Ponto hips = cintura();
		Ponto leftarm = leftArm();
		Ponto rightarm = rightArm();
		Ponto neck = pescoco();
		glBegin(GL_LINES);
			glVertex3f(hips.x,hips.y,0);
			glVertex3f(neck.x,neck.y,0);

			glVertex3f(leftfeet.x,leftfeet.y,0);
			glVertex3f(hips.x,hips.y,0);

			glVertex3f(rightfeet.x,rightfeet.y,0);
			glVertex3f(hips.x,hips.y,0);
		glEnd();
		Ponto rightelbow = getJunta(neck,rightarm+neck,tamanhoBraco(),tamanhoAntebraco());
		Ponto leftelbow = getJunta(neck,leftarm+neck,tamanhoBraco(),tamanhoAntebraco());
		glPushMatrix();
			glTranslatef(neck.x,neck.y,0);
			glRotatef(getAngle()*180.0/PI,0,0,-1);
			glBegin(GL_LINES);
				glVertex3f(0,0,-1);
				glVertex3f(leftelbow.x,leftelbow.y,-1);
				glVertex3f(leftelbow.x,leftelbow.y,-1);
				glVertex3f(leftarm.x,leftarm.y,-1);
				
				glVertex3f(0,0,1);
				glVertex3f(rightelbow.x,rightelbow.y,1);
				glVertex3f(rightelbow.x,rightelbow.y,1);
				glVertex3f(rightarm.x,rightarm.y,1);
			glEnd();
			if (weapon != NULL) weapon->desenha();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(neck.x,neck.y-10,0);
			drawCircle(10,30);
		glPopMatrix();
	glPopMatrix();
}


Linha Shooter::getBaseLine() {
	return Linha(leftFeet(), rightFeet());
}

Polygon Shooter::getCollision() {
	Polygon poly;
	Linha a(leftFeet(),rightFeet());
	Linha b(rightFeet(),cintura());
	Linha c(cintura(),rightArm());
	Linha d(rightArm(),pescoco());
	Linha e(pescoco(),leftArm());
	Linha f(leftArm(),cintura());
	Linha g(cintura(),leftFeet());
	poly.addLinha(a);
	poly.addLinha(b);
	poly.addLinha(c);
	poly.addLinha(d);
	poly.addLinha(e);
	poly.addLinha(f);
	poly.addLinha(g);
	return poly;
}

void Shooter::setAim(double x, double y) {
	aim.x = x;
	aim.y = y;				
}
