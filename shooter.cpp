#include <math.h>
#include "shooter.h"
#include "gravity.h"

Shooter::Shooter(Game* agame, Ponto pos, Ponto speed) {
	weapon = NULL;
    setPosition(pos.x, pos.y);
    setSpeed(speed.x, speed.y);
	game = agame;
	game->gravityManager->subscribe(this);
	maxspeed.x = 5;
	maxspeed.y = 20;
}

void Shooter::equip(Weapon* aweapon) {
	//desequipar a anterior aqui mais tarde
	weapon = aweapon;
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
Ponto Shooter::getCotovelo(Ponto ombro, Ponto hand) {
	double a = tamanhoBraco();
	double b = tamanhoAntebraco();
	double d = distance(ombro,hand);
	double area = areaTriangle(a,b,d);
	double ylinha = 2.0*area/d;
	double xlinha = sqrt(a*a-ylinha*ylinha);
	double sinTheta = (hand.y-ombro.y)/d;
	double cosTheta = (hand.x-ombro.x)/d;
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
	Ponto gameaim(aim.x+game->camera.x,aim.y+game->camera.y);
	Ponto gameneck(pescoco().x+getX(),pescoco().y+getY());
	double hyp = sqrt((gameaim.x-gameneck.x)*(gameaim.x-gameneck.x) + 
					  (gameaim.y-gameneck.y)*(gameaim.y-gameneck.y));
	if (gameaim.y <= gameneck.y)
		return -acos((-gameaim.x+gameneck.x)/hyp);
	else
		return acos((-gameaim.x+gameneck.x)/hyp);
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
		Ponto rightelbow = getCotovelo(neck,rightarm+neck);
		Ponto leftelbow = getCotovelo(neck,leftarm+neck);
		glPushMatrix();
			glTranslatef(neck.x,neck.y,0);
			glRotatef(getAngle()*180.0/PI,0,0,-1);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(leftelbow.x,leftelbow.y,0);
				glVertex3f(leftelbow.x,leftelbow.y,0);
				glVertex3f(leftarm.x,leftarm.y,0);
				
				glVertex3f(0,0,0);
				glVertex3f(rightelbow.x,rightelbow.y,0);
				glVertex3f(rightelbow.x,rightelbow.y,0);
				glVertex3f(rightarm.x,rightarm.y,0);
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
	Ponto leftfeet = leftFeet();
	Ponto rightfeet = rightFeet();
	Linha ret(leftfeet.x+getX(),leftfeet.y+getY(),rightfeet.x+getX(),rightfeet.y+getY());
	return ret;
}

void Shooter::setAim(double x, double y) {
	aim.x = x;
	aim.y = y;				
}
