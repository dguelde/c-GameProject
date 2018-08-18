//state class for use by controller

class State //master class for states
{
	update(){}
	display(){}

};


class StartState : public State//a state to handle initial game setup, log-in, etc
{

};


class ActionState : public State//a game state for action phase
{

};