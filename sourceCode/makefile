#lots of warnings…


#FILES = main.cpp gameObjects.cpp factory.cpp

CC = g++ 

CFLAGS = -w -O3 -Wall



#LINKERS = -framework OpenGL -framework GLUT -framework OpenGL


#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLAGS=-O3 -Wall
LINKERS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLAGS=-O3 -Wall  -w
LINKERS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLAGS=-std=c++11 -O3 -Wall -w
LINKERS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif


#TARGET = game

#This is the target that compiles our executable
#all : $(OBJS)
#	$(CC) $(FILES) $(CFLAGS) $(LINKERS) -o $(EXE)

default: game

game: main.o GameController.o state.o  gameObjects.o factory.o pathfinder.o  
	$(CC)  main.o gameObjects.o  factory.o pathfinder.o GameController.o state.o   -o game $(CFLAGS) $(LINKERS)

main.o: main.cpp 
	$(CC) $(CFLAGS) $(LINKERS) -c main.cpp

gameObjects.o: gameObjects.cpp
	$(CC) $(CFLAGS) $(LINKERS) -c gameObjects.cpp 

factory.o: factory.cpp
	$(CC) $(CFLAGS) -c factory.cpp

pathfinder.o: pathfinder.cpp
	$(CC) $(CFLAGS) -c pathfinder.cpp

GameController.o: GameController.cpp GameController.h
	$(CC) $(CFLAGS) -c GameController.cpp GameController.h

state.o: state.cpp state.h
	$(CC) $(CFLAGS) -c state.cpp state.h








clean:
	$(CLEAN)
