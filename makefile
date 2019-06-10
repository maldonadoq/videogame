SRCS	= main.cpp src/cuarto.cpp src/mapa.cpp src/juego.cpp \
			src/tmanager.cpp src/jugador.cpp src/utils.cpp \
			src/gestor.cpp src/enemigo.cpp src/random.cpp \
			src/modelo.cpp src/generar_nivel.cpp src/puerta.cpp \
			src/ovni.cpp src/monstruo.cpp
CC		= g++ -std=c++17
OPTS	= -O3
INCD	= inc

OBJS	= $(SRCS:.cpp=.o)
LIBS	= -lGL -lglut -lGLU -lfreeimage -lsfml-system -lsfml-audio

all: main

main: $(OBJS)
	$(CC) -o main.out $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(OPTS) -c $< -o $@

# delete lib with clean 
clean:
	rm -f $(OBJS) *.out