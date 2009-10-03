#include "geometry.h"

Linha::Linha(double x1,double y1,double x2, double y2) {
	vertices[0].x = x1;
	vertices[0].y = y1;
	vertices[1].x = x2;
	vertices[1].y = y2;
}

void Linha::desenha() {
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex3f(vertices[0].x, vertices[0].y, 0.0f); // origin of the line
		glVertex3f(vertices[1].x, vertices[1].y, 0.0f); // origin of the line
	glEnd( );
}
