all: desenha
	

desenha: desenha_plataformas.cpp plataforma.cpp plataforma.h plataformas.cpp
	g++ -lSDL -lGL desenha_plataformas.cpp plataforma.cpp plataformas.cpp
