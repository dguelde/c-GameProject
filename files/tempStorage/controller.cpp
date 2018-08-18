// a simple state controller/handler

#include "state.cpp"


class GameController{
public:
	GameController();
	void setState(State* state);
	void update();
 	void display();
	void handleState();
protected:
	State* currentState;
};

GameController::GameController()
{
	currentState = new StartState();
}

void GameController::setState(State* newState)
{
	currentState = newState;
}

void GameController::update()
{
	currentState->update();
}

void GameController::display()
{
	currentState->display();
}