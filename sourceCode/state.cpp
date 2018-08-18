#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <list>
#include <ctime>
#include "state.h"
#include "openGL.cpp"

int State::unitLocationsX[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int State::unitLocationsY[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

StartState::StartState(){

	
};

StartState::StartState(GameController* Context)
{

	static int unitLocationsX[10];
	static int unitLocationsY[10];
	context = Context;

}


void StartState::display()
{
	std::cout << "Enter x coordinate for home base: ";
	std::cin >> xCoord;
	std::cout << "Enter y coordinate for home base: ";
	std::cin >> yCoord;
	unitLocationsX[0]=xCoord;
	unitLocationsY[0]=yCoord;
	for (int index=1;index<5;index++)
	{
	std::cout << "Enter x coordinate for defender: ";
	std::cin >> xCoord;
	std::cout << "Enter y coordinate for defender: ";
	std::cin >> yCoord;
	unitLocationsX[index]=xCoord;
	unitLocationsY[index]=yCoord;
	}
	

return;
}



void ActionState::display()
{
	Draw(0,nullptr, unitLocationsX, unitLocationsY); //arguments are basically dummies~the openGL function wants to be main(), so it expects main's standard arguments...
return;
}

ActionState::ActionState()
{
	
}

ActionState::ActionState(GameController* Context)
{
	context = Context;
}