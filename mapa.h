#ifndef MAPA_H
#define MAPA_H

#include <list>

#include "player.h"
#include "geometry.h"

class Player;

class Mapa {
	private:
		Ponto tamanho;
		Player *jogador;
		GravityManager *gravidade;
		std::list<Linha> linhas;
	public:
		Mapa(double xmax, double ymax, Player *p, GravityManager *g);
		void novaLinha(double xmin, double ymin, double xmax, double ymax);
		void desenha();
		double xmax();
		double ymax();
};

#endif
