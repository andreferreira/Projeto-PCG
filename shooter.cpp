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
	realLeftfeet.x = -8;
	realLeftfeet.y = 0;
	realRightfeet.x = 8;
	realRightfeet.y = 0;
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

	weapon->position = getPosition() + pescoco();
	weapon->fire(tip,angle);
}


Ponto Shooter::leftFeet() {
	return realLeftfeet;
}

Ponto Shooter::rightFeet() {
	return realRightfeet;
}

Ponto Shooter::imaginaryLeftfeet(int t) {
	Ponto pe(0,0);
	if (onGround && abs(getSpeedX()) < 0.05) {
		pe.x = -8;
		pe.y = 0;
	}
	else if (onGround) {
		if (getSpeedX() < 0)
			t = -t;
		t *= 1.0+abs(getSpeedX());
		pe.x = 6*cos(PI+t/30.0);
		pe.y = 2.5*sin(PI+t/30.0)-2.5;
	}
	else {
		pe.x = -4;
		pe.y = -19;
	}
	return pe;
}

Ponto Shooter::imaginaryRightfeet(int t) {
	Ponto pe(0,0);
	if (onGround && abs(getSpeedX()) < 0.05) {
		pe.x = 8;
		pe.y = 0;
	}
	else if (onGround) {
		if (getSpeedX() < 0)
			t = -t;
		t *= 1.0+abs(getSpeedX());
		pe.x = 6*cos(t/30.0);
		pe.y = 2.5*sin(t/30.0)-2.5;
	}
	else {
		pe.x = 4;
		pe.y = -19;
	}
	return pe;
}

double sign(double n) {
	if (n == 0.0)
		return 0.0;
	if (n < 0.0)
		return -1.0;
	if (n > 0.0)
		return 1.0;
}

void Shooter::animate() {
	static int t = 0;
	
	Ponto il = imaginaryLeftfeet(t);
	Ponto ir = imaginaryRightfeet(t);
	t++;
	
	realLeftfeet.x += sign(il.x - realLeftfeet.x)*0.5;
	realLeftfeet.y += sign(il.y - realLeftfeet.y)*0.5;
	
	realRightfeet.x += sign(ir.x - realRightfeet.x)*0.5;
	realRightfeet.y += sign(ir.y - realRightfeet.y)*0.5;
	
	double dl = distance(il,realLeftfeet);
	double dr = distance(ir,realRightfeet);
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
    Ponto c(0,-40);
    return c;
}

Ponto Shooter::pescoco() {
	Ponto hips = cintura();
	Ponto neck(hips.x,hips.y-30);
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
	return 23.0;
}

double Shooter::tamanhoAntebraco() {
	return 16.0;
}

double Shooter::tamanhoCoxa() {
	return 20.0;
}

double Shooter::tamanhoPerna() {
	return 22.0;
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
#include <iostream>
void Shooter::desenha() {
	glPushMatrix();
		glTranslatef(getX(),getY(),0);
		Ponto leftfeet = leftFeet();
		Ponto rightfeet = rightFeet();
		glTranslatef(0,std::min(-rightfeet.y,-leftfeet.y),0);
		Ponto hips = cintura();
		Ponto leftarm = leftArm();
		Ponto rightarm = rightArm();
		Ponto neck = pescoco();
		Ponto rightknee = getJunta(rightfeet,hips,tamanhoPerna(),tamanhoCoxa()) + rightfeet;
		Ponto leftknee = getJunta(leftfeet,hips,tamanhoPerna(),tamanhoCoxa()) + leftfeet;
		glBegin(GL_LINES);
			glVertex3f(hips.x,hips.y,0);
			glVertex3f(neck.x,neck.y,0);

			glVertex3f(leftfeet.x,leftfeet.y,0);
			glVertex3f(leftknee.x,leftknee.y,0);
			
			glVertex3f(leftknee.x,leftknee.y,0);
			glVertex3f(hips.x,hips.y,0);

			glVertex3f(rightfeet.x,rightfeet.y,0);
			glVertex3f(rightknee.x,rightknee.y,0);
			
			glVertex3f(rightknee.x,rightknee.y,0);
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
			glTranslatef(neck.x,neck.y-11,0);
			drawCircle(11,30);
		glPopMatrix();
	glPopMatrix();
}


Linha Shooter::getBaseLine() {
	Ponto left(-8,0);
	Ponto right(8,0);
	return Linha(left, right);
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
