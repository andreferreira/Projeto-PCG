#include "geometry.h"
#include "math.h"
#include <vector>

const double PI = 3.14159265358979323846;

Linha::Linha(double x1,double y1,double x2, double y2) {
	vertices[0].x = x1;
	vertices[0].y = y1;
	vertices[1].x = x2;
	vertices[1].y = y2;
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
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex3f(vertices[0].x, vertices[0].y, 0.0f); // origin of the line
		glVertex3f(vertices[1].x, vertices[1].y, 0.0f); // origin of the line
	glEnd( );
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

void drawCircle(double radius, int lines)
{
	double i2rad = PI/(lines/2.0);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i < lines; i++) {
		double degInRad = i*i2rad;
		glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
	}

	glEnd();
}
