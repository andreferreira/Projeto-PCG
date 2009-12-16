#include "mapa.h"
#include "maploader.h"
#include "weaponitem.h"

Mapa::Mapa(std::string name, Game* g) {
	game = g;
	MapLoader loader;
	loader.load(name,this);
}

Mapa::~Mapa() {
	std::list<Platform*>::iterator it;
	for (it = platforms.begin(); it != platforms.end(); it++)
		delete (*it);
	game->removePlatforms();
}

void Mapa::setTamanho(double width, double height) {
	tamanho.x = width;
	tamanho.y = height;
}

void Mapa::setSpawn(Ponto spawn) {
	game->setSpawn(spawn);
}

void Mapa::novaPlataforma(double xmin, double ymin, double xmax, double ymax, bool pass, double r, double g, double b) {
	Linha l(xmin, ymin, xmax, ymax);
	Platform *plat = new Platform(l, pass, r, g, b);
	platforms.push_front(plat);
	game->addPlatform(plat);
}

void Mapa::dropWeapon(std::string name, Ponto p) {
	WeaponItem *a = game->dropWeapon(name);
	a->setPosition(p.x, p.y);
	items.push_front(a);
}

void Mapa::desenha() {
	std::list<Platform*>::iterator itP;
	for (itP = platforms.begin(); itP != platforms.end(); itP++)
		(*itP)->desenha();
	std::list<WeaponItem*>::iterator itW;
	for (itW = items.begin(); itW != items.end(); itW++)
		(*itW)->desenha();
}

double Mapa::xmax() {
	return tamanho.x;
}

double Mapa::ymax() {
	return tamanho.y;
}

void Mapa::move() {
	std::list<WeaponItem*>::iterator it;
	for (it = items.begin(); it != items.end(); it++)
		(*it)->move();	
}
