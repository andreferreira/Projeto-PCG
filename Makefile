all: desenha_plataformas.cpp plataforma.cpp plataforma.h
	g++ -lSDL -lGL -o desenha desenha_plataformas.cpp plataforma.cpp
