SRCS	= main.cpp src/cuarto.cpp src/mapa.cpp src/juego.cpp \
			src/tmanager.cpp
CC		= g++ -std=c++17
OPTS	= -O3
INCD	= inc

OBJS	= $(SRCS:.cpp=.o)
LIBS	= -lGL -lglut -lGLU -lfreeimage

all: main

main: $(OBJS)
	$(CC) -o main.out $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(OPTS) -c $< -o $@

# delete lib with clean 
clean:
	rm -f $(OBJS) *.out