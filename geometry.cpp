#include "geometry.h"
#include "math.h"
#include <vector>

Linha::Linha(double x1,double y1,double x2, double y2) {
	vertices[0].x = x1;
	vertices[0].y = y1;
	vertices[1].x = x2;
	vertices[1].y = y2;
}

void Linha::translate(Ponto v) {
	vertices[0] = vertices[0] + v;
	vertices[1] = vertices[1] + v;
}

Rect::Rect(double x1,double y1,double x2, double y2) {
	vertices[0].x = x1;
	vertices[0].y = y1;
	vertices[1].x = x2;
	vertices[1].y = y2;
	normaliza();
}

void Rect::normaliza() {
	double xmin,xmax,ymin,ymax;
	xmin = std::min(vertices[0].x,vertices[1].x);
	xmax = std::max(vertices[0].x,vertices[1].x);
	ymin = std::min(vertices[0].y,vertices[1].y);
	ymax = std::max(vertices[0].y,vertices[1].y);
	vertices[0].x = xmin;
	vertices[1].x = xmax;
	vertices[0].y = ymin;
	vertices[1].y = ymax;
}

void Linha::desenha() {
	glColor3f(color[0],color[1],color[2]);
	glBegin(GL_LINES);
		glVertex3f(vertices[0].x, vertices[0].y, -1.5f); // origin of the line
		glVertex3f(vertices[1].x, vertices[1].y, -1.5f); // origin of the line
	glEnd( );
	glColor3f(0,0,0);
}

void Polygon::desenha() {
	int n = linhas.size();
	for (int i = 0; i < n; i++) {
		linhas[i].desenha();
	}
}

void Polygon::translate(Ponto v) {
	for (int i = 0; i < linhas.size(); i++)
		linhas[i].translate(v);
}

double operator*(const Ponto &a, const Ponto &b) {
	return a.x * b.y - b.x * a.y; 
}

Ponto operator-(const Ponto &a, const Ponto &b) {
	Ponto ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

Ponto operator+(const Ponto &a, const Ponto &b) {
	Ponto ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return ret;
}

double distance(const Ponto &a,const Ponto &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void drawCircle(double radius, int lines)
{
	double i2rad = PI/(lines/2.0);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	for (int i=0; i < lines; i++) {
		double degInRad = i*i2rad;
		glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,0);
	}
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i < lines; i++) {
		double degInRad = i*i2rad;
		glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,0);
	}

	glEnd();
}

//calcula se a direcao dos segmentos p0p1 p1p2 é horaria, antihoraria ou se sao colineares
double direction(const Ponto &p0,const Ponto &p1,const Ponto &p2) {
	return (p2 - p0) * (p1 - p0);
}

bool onsegment(const Ponto &pi,const Ponto &pj,const Ponto &pk) { 
	if ((std::min(pi.x, pj.x) <= pk.x && pk.x <= std::max(pi.x, pj.x)) &&
	    (std::min(pi.y, pj.y) <= pk.y && pk.y <= std::max(pi.y, pj.y)))
		return true; 
	else 
		return false;
}

bool linesIntersect(const Linha a,const Linha b) {
	Ponto p1 = a.vertices[0];
	Ponto p2 = a.vertices[1];
	Ponto p3 = b.vertices[0];
	Ponto p4 = b.vertices[1];
	double d1 = direction(p3, p4, p1);
	double d2 = direction(p3, p4, p2);
	double d3 = direction(p1, p2, p3);
	double d4 = direction(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
	   ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true; 
	else if (d1 == 0.0 && onsegment(p3, p4, p1)) 
		return true;
	else if (d2 == 0.0 && onsegment(p3, p4, p2))
		return true; 
	else if (d3 == 0.0 && onsegment(p1, p2, p3))
		return true; 
	else if (d4 == 0.0 && onsegment(p1, p2, p4))
		return true;
	else
		return false;
}
#include <iostream>
double timeToIntersection(const Linha a,const Linha b) {
	double x1 = a.vertices[0].x, y1 = a.vertices[0].y,
		   x2 = a.vertices[1].x, y2 = a.vertices[1].y,
		   x3 = b.vertices[0].x, y3 = b.vertices[0].y,
		   x4 = b.vertices[1].x, y4 = b.vertices[1].y;
	
	double denominator = ((y4 - y3) * (x2 - x1) - (x4 - x3)*(y2 - y1));
	double numeratorA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3));
	double numeratorB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3));
	double ua,ub;
	if (denominator == 0) {
		ua = 9999;
		ub = 9999;
		return ua;
	}
	ua = numeratorA / denominator;
	ub = numeratorB / denominator;
	return ua;
}

double abs(double x) {
	if (x < 0.0)
		return -x;
	return x;
}

double sign(double n) {
	if (n == 0.0)
		return 0.0;
	if (n < 0.0)
		return -1.0;
	if (n > 0.0)
		return 1.0;
}

double closerToZero(double a, double b) {
	if (abs(a) < abs(b))
		return a;
	return b;
}
