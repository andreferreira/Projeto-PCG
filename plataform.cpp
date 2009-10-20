#include "plataform.h"

Plataform::Plataform(Linha aline) : line(aline) {
	passable = false;
}

void Plataform::desenha() {
	line.desenha();
}
