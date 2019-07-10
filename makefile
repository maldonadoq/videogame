CC		= g++ -std=c++17
SRCS	= 	main.cpp src/juego.cpp src/cuarto.cpp src/mapa.cpp \
			src/tmanager.cpp src/jugador.cpp src/utils.cpp \
			src/gestor.cpp src/enemigo.cpp src/random.cpp \
			src/modelo.cpp src/generar_nivel.cpp src/puerta.cpp \
			src/ovni.cpp src/monstruo.cpp src/boss.cpp src/hydra.cpp \
			src/sentinel.cpp src/item.cpp src/bala.cpp src/motor.cpp \
			src/boton.cpp src/listen.cpp src/puerta_salida.cpp
OBJS	= $(SRCS:.cpp=.o)

LEAP_INC 		= -I"leap/include"
IRRKLANG_INC 	= -I"irrklang/include"

LEAP_LIB 		= -L"/usr/lib" leap/lib/x64/libLeap.so -Wl,-rpath,leap/lib/x64
IRRKLANG_LIB 	= -L"/usr/lib" irrklang/bin/linux-gcc-64/libIrrKlang.so
OPENGL_LIB		= -lGL -lglut -lGLU -lfreeimage -pthread

all: main

main: $(OBJS)
	$(CC) -o main.out $(OBJS) $(OPENGL_LIB) $(IRRKLANG_LIB) $(LEAP_LIB)

%.o: %.cpp
	$(CC) -c $< -o $@ $(IRRKLANG_INC) $(LEAP_INC)

# delete lib with clean 
clean:
	rm -f src/*.o *.out