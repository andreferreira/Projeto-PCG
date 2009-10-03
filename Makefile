all: a.out
	

a.out: desenha_plataformas.cpp geometry.cpp geometry.h plataformas.cpp luaenv.cpp luaenv.h
	g++ -lSDL -lGL desenha_plataformas.cpp geometry.cpp plataformas.cpp luaenv.cpp liblua.a

clean:
	rm a.out
