
#include <iostream>
#include "GameController.h"



int argc; //http://stackoverflow.com/questions/16677347/how-to-use-int-argc-char-argv-outside-of-main-function-in-c
char **argv; //ugly, but it works...

int main(int ac, char** av)
{
	argc = ac;
  	argv = av;
	GameController* controller = GameController::makeInstance();
	while (true)
	{
		controller->display();
		controller->update();
			
	}
	

}