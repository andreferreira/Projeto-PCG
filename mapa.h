#ifndef MAPA_H
#define MAPA_H

#include <list>
#include <string>

#include "geometry.h"
#include "platform.h"
#include "game.h"

class Player;
class Game;
class WeaponItem;

class Mapa {
	private:
		Ponto tamanho;
		std::list<Platform*> platforms;
	public:
		Game *game;
		std::list<WeaponItem*> items;
		Mapa(std::string name, Game *g);
		~Mapa();
		void novaPlataforma(double xmin, double ymin, double xmax, double ymax, bool pass, double r, double g, double b);
		void dropWeapon(std::string name, Ponto p);
		void desenha();
		void setSpawn(Ponto spawn);
		double xmax();
		double ymax();
		void setTamanho(double width, double height);
		void move();
};

#endif
