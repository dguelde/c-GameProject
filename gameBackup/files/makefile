
#FILES = main.cpp gameObjects.cpp factory.cpp

CC = g++

CFLAGS = -w -O3 -Wall

CLEAN = rm -f $(EXE) *.o

LINKERS = -framework OpenGL -framework GLUT -framework OpenGL


#TARGET = game

#This is the target that compiles our executable
#all : $(OBJS)
#	$(CC) $(FILES) $(CFLAGS) $(LINKERS) -o $(EXE)

default: game

game: main.o gameObjects.o factory.o pathfinder.o
	$(CC) $(CFLAGS) $(LINKERS) -o game main.o gameObjects.o factory.o pathfinder.o

main.o: main.cpp
	$(CC) $(CFLAGS) $(LINKERS) -c main.cpp

gameObjects.o: gameObjects.cpp
	$(CC) $(CFLAGS) $(LINKERS) -c gameObjects.cpp

factory.o: factory.cpp
	$(CC) $(CFLAGS) -c factory.cpp

pathfinder.o: pathfinder.cpp
	$(CC) $(CFLAGS) -c pathfinder.cpp

clean:
	$(CLEAN)
