SRCS	= 	main.cpp src/juego.cpp src/cuarto.cpp src/mapa.cpp \
			src/tmanager.cpp src/jugador.cpp src/utils.cpp \
			src/gestor.cpp src/enemigo.cpp src/random.cpp \
			src/modelo.cpp src/generar_nivel.cpp src/puerta.cpp \
			src/ovni.cpp src/monstruo.cpp src/item.cpp src/hydra.cpp \
			src/sentinel.cpp src/bala.cpp src/motor.cpp src/boton.cpp
CC		= g++ -std=c++17

OBJS	= $(SRCS:.cpp=.o)

INC 	= -I"irrklang/include"
LIBS	= -lGL -lglut -lGLU -lfreeimage -lsfml-system -lsfml-audio -L"/usr/lib" irrklang/bin/linux-gcc-64/libIrrKlang.so -pthread

all: main

main: $(OBJS)
	$(CC) -o main.out $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(INC)

# delete lib with clean 
clean:
	rm -f src/*.o *.o *.out