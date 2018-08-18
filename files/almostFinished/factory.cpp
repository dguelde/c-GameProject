#include <string>
#include "gameObjects.cpp"



class Factory
{
public:
	Factory() {};
	GameObject* createObject(std::string name)
	{
		
		if(name=="Enemy")
		{
			GameObject * newObject = new Enemy();
			return newObject;
		}
		else if(name=="Defender")
		{
			GameObject * newObject = new Defender();
			return newObject;
		}
		if(name=="DefenderBase")
		{
			GameObject * newObject = new DefenderBase();
			return newObject;
		}
	}
};

class GameSquareFactory
{
public:
	GameSquareFactory(){};
	GameSquare* createSquare(std::string name)
	{
		if(name == "Land")
		{
			GameSquare *newObject = new LandSquare();
			return newObject;
		}

	}
};
