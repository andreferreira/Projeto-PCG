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
	acorde.o \
	nota.o \
	
SRCS = $(OBJS,.o=.cpp) 

all: bigstick

bigstick: $(OBJS)
	g++ -o bigstick -O3 -lSDL -lGL -lcwiid $(OBJS) liblua.a

.cpp.o:
	g++ -O3 -c $<

clean:
	rm -f bigstick *.o

ubuntu: $(OBJS)
	g++ -O3 -lSDL -lGL -llua5.1 -lcwiid $(OBJS)
