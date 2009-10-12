OBJS = \
	main.o \
	geometry.o \
	plataformas.o \
	luaenv.o \
	player.o \
	game.o \
	timer.o \
	
	
SRCS = $(OBJS,.o=.cpp) 

all: a.out

a.out: $(OBJS)
	g++ -lSDL -lGL $(OBJS) liblua.a

.cpp.o:
	g++ -c $<

clean:
	rm a.out *.o
