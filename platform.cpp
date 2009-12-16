#include "platform.h"
#include "math.h"

Platform::Platform(Linha aline, bool pass, double r, double g, double b): line(aline), passable(pass) { 
	line.color[0] = r;
	line.color[1] = g;
	line.color[2] = b;
	}

void Platform::desenha() {
	line.desenha();
}

double Platform::angle() {
	double x1 = line.vertices[0].x, x2 = line.vertices[1].x,
		   y1 = line.vertices[0].y, y2 = line.vertices[1].y;
	double size = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	if (size == 0.0)
		return 0;
	return asin(abs(y2-y1)/size);
}
