#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include "state.h"
class state;
//uses a singleton pattern to ensure only one instance of GameController is created
class GameController{
friend class state;
public:
	static GameController* makeInstance();
	void setState(std::string state);
	void update();
 	void display();
protected:
	State* currentState;
	State* actionState;
	State* startState;
	GameController(); //private for singleton
	static GameController* uniqueInstance;
	static bool created;

};



#endif