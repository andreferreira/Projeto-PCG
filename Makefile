OBJS = \
	main.o \
	geometry.o \
	luaenv.o \
	shooter.o \
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
	maploader.o \
	weaponmanager.o \
	configmanager.o \
	shot.o \
	shotmanager.o \
	controlewii.o \
	collision.o \
	enemy.o \
	weaponitem.o \
	enemymanager.o \

	
SRCS = $(OBJS,.o=.cpp) 

all: a.out

a.out: $(OBJS)
	g++ -lSDL -lGL -lcwiid $(OBJS) liblua.a

.cpp.o:
	g++ -c $<

clean:
	rm -f a.out *.o

ubuntu: $(OBJS)
	g++ -lSDL -lGL -llua5.1 -lcwiid $(OBJS)
