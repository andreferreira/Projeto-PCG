#ifndef MAPA_H
#define MAPA_H

#include <list>
#include <string>

#include "geometry.h"
#include "platform.h"
#include "game.h"

class Player;
class Game;

class Mapa {
	private:
		Ponto tamanho;
		Game *game;
		std::list<Platform*> platforms;
	public:
		Mapa(std::string name, Game *g);
		~Mapa();
		void novaPlataforma(double xmin, double ymin, double xmax, double ymax, bool pass);
		void desenha();
		void setSpawn(Ponto spawn);
		double xmax();
		double ymax();
		void setTamanho(double width, double height);
};

#endif
