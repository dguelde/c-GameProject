//state class for use by controller

#ifndef STATE_H
#define STATE_H


#include <vector>





class GameController;



class State //master class for states
{

public:
	State(){};

	virtual void update(){};
	virtual void display(){};
	static int unitLocationsX[10];
	static int unitLocationsY[10];
protected:
	GameController* context;

};

class StartState : public State//a state to handle initial game setup, log-in, initial menus, etc
{
public:
	StartState();
	StartState(GameController* Context);
	void update();
	void display();


protected:
	int xCoord;
	int yCoord;

	
};


class ActionState : public State//a game state for action phase
{
public:
	ActionState();
	ActionState(GameController* Context);
	void update();
	void display();

};




#endif