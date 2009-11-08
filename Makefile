OBJS = \
	main.o \
	geometry.o \
	luaenv.o \
	player.o \
	game.o \
	timer.o \
	controle.o \
	thing.o \
	gravity.o \
	mapa.o \
	platform.o \
	controleteclado.o \
	weapon.o \
	
SRCS = $(OBJS,.o=.cpp) 

all: a.out

a.out: $(OBJS)
	g++ -lSDL -lGL $(OBJS) liblua.a

.cpp.o:
	g++ -c $<

clean:
	rm -f a.out *.o

bruno: $(OBJS)
	g++ -lSDL -lGL -llua5.1 $(OBJS)
