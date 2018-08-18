// a simple state controller/handler

#include "state.cpp'"

class GameController{
public:
	void updateState();
	void displayState();

private:
	gameState* currentState;

};

