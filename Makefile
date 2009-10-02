all: a.out
	

a.out: desenha_plataformas.cpp plataforma.cpp plataforma.h plataformas.cpp scriptloader.cpp scriptloader.h
	g++ -lSDL -lGL desenha_plataformas.cpp plataforma.cpp plataformas.cpp scriptloader.cpp liblua.a

clean:
	rm a.out
