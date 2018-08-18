// a simple state controller/handler

#include <stddef.h>
#include <iostream>
#include "GameController.h"



GameController* GameController::uniqueInstance = nullptr;
bool GameController::created = false;


GameController::GameController() //this is private
{
	
	startState = new StartState(this);
	actionState = new ActionState(this);
	currentState = startState;
	
}

GameController* GameController::makeInstance() //public, singleton pattern will only create one controller
{
	if(created==false)
	{
		uniqueInstance = new GameController();
		created = true;
	}
	return uniqueInstance;
}

void GameController::setState(std::string state)
{
	if (state == "start")
	{
		currentState = startState;
	}
	if(state == "action")
	{
		currentState = actionState;
	}
}

void GameController::update()
{
	currentState->update();
}

void GameController::display()
{
	currentState->display();
}



//update to real functions later.....


void StartState::update()
{
	
	
	context->setState("action");
}

void ActionState::update()
{

	context->setState("start");
}

