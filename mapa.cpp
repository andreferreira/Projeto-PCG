#include "mapa.h"

Mapa::Mapa(double xmax, double ymax, Player *p, GravityManager *g): jogador(p), gravidade(g) {
	tamanho.x = xmax;
	tamanho.y = ymax;
}

void Mapa::novaPlataforma(double xmin, double ymin, double xmax, double ymax) {
	Linha l(xmin, ymin, xmax, ymax);
	Plataform *plat = new Plataform(l);
	linhas.push_front(plat);
	gravidade->addPlatform(plat);
}

void Mapa::desenha() {
	std::list<Plataform*>::iterator it;
	for (it = linhas.begin(); it != linhas.end(); it++)
		(*it)->desenha();
}

double Mapa::xmax() {
	return tamanho.x;
}

double Mapa::ymax() {
	return tamanho.y;
}
