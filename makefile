SRCS	= 	src/cuarto.cpp src/mapa.cpp \
			src/tmanager.cpp src/jugador.cpp src/utils.cpp \
			src/gestor.cpp src/enemigo.cpp src/random.cpp \
			src/modelo.cpp src/generar_nivel.cpp src/puerta.cpp \
			src/ovni.cpp src/monstruo.cpp src/item.cpp src/hydra.cpp \
			src/sentinel.cpp src/bala.cpp src/motor.cpp src/boton.cpp
CC		= g++ -std=c++17
INCD	= inc

IRR 	= -I"irrklang/include" -L"/usr/lib" irrklang/bin/linux-gcc-64/libIrrKlang.so -pthread

OBJS	= $(SRCS:.cpp=.o)
LIBS	= -lGL -lglut -lGLU -lfreeimage -lsfml-system -lsfml-audio

all: pre main

pre: src/juego.cpp main.cpp
	$(CC) -c src/juego.cpp -o src/juego.o $(IRR)
	$(CC) -c main.cpp -o main.o $(IRR)

main: $(OBJS)
	$(CC) -o main.out main.o src/juego.o $(OBJS) $(LIBS) $(IRR)

%.o: %.cpp
	$(CC) -c $< -o $@

# delete lib with clean 
clean:
	rm -f $(OBJS) *.out *.o