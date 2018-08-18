// factory

#ifndef FACTORY_H
#define FACTORY_H

#include "gameObjects.cpp"
#include "factory.cpp"




class Factory{
public:
	Factory() {};
	GameObject* createObject(std::string name) {};
};


#endif