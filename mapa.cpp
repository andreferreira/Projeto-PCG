#include "mapa.h"

Mapa::Mapa(double xmax, double ymax, Player *p, GravityManager *g): jogador(p), gravidade(g) {
	tamanho.x = xmax;
	tamanho.y = ymax;
}

void Mapa::novaLinha(double xmin, double ymin, double xmax, double ymax) {
	Linha l(xmin, ymin, xmax, ymax);
	linhas.push_front(l);
	gravidade->addPlatform(&linhas.front());
}

void Mapa::desenha() {
	std::list<Linha>::iterator it;
	for (it = linhas.begin(); it != linhas.end(); it++)
		it->desenha();
}

double Mapa::xmax() {
	return tamanho.x;
}

double Mapa::ymax() {
	return tamanho.y;
}
