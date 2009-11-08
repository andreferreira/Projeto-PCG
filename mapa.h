#ifndef MAPA_H
#define MAPA_H

#include <list>
#include <string>

#include "player.h"
#include "geometry.h"
#include "platform.h"
#include "game.h"

class Player;
class Game;

class Mapa {
	private:
		Ponto tamanho;
		Game *game;
		std::list<Platform*> linhas;
	public:
		Mapa(std::string name, Game *g);
		void novaPlataforma(double xmin, double ymin, double xmax, double ymax, bool pass);
		void desenha();
		double xmax();
		double ymax();
		void setTamanho(double width, double height);
};

#endif
