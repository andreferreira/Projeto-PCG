OBJS = \
	desenha_plataformas.o \
	geometry.o \
	plataformas.o \
	luaenv.o \
	
	
SRCS = $(OBJS,.o=.cpp) 

all: a.out

a.out: $(OBJS)
	g++ -lSDL -lGL $(OBJS) liblua.a

.cpp.o:
	g++ -c $<

clean:
	rm a.out *.o
