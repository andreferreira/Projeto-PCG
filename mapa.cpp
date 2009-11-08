#include "mapa.h"
#include "maploader.h"

Mapa::Mapa(std::string name, Game* g) {
	game = g;
	MapLoader loader;
	loader.load(name,this);
}

void Mapa::setTamanho(double width, double height) {
	tamanho.x = width;
	tamanho.y = height;
}

void Mapa::novaPlataforma(double xmin, double ymin, double xmax, double ymax, bool pass) {
	Linha l(xmin, ymin, xmax, ymax);
	Platform *plat = new Platform(l, pass);
	linhas.push_front(plat);
	game->addPlatform(plat);
}

void Mapa::desenha() {
	std::list<Platform*>::iterator it;
	for (it = linhas.begin(); it != linhas.end(); it++)
		(*it)->desenha();
}

double Mapa::xmax() {
	return tamanho.x;
}

double Mapa::ymax() {
	return tamanho.y;
}
