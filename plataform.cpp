#include "plataform.h"

Plataform::Plataform(Linha aline, bool pass): line(aline), passable(pass) { }

void Plataform::desenha() {
	line.desenha();
}
