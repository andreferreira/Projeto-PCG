#include "platform.h"

Platform::Platform(Linha aline, bool pass): line(aline), passable(pass) { }

void Platform::desenha() {
	line.desenha();
}
