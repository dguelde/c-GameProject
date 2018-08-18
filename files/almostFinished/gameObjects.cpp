

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



typedef struct {
	int x;
	int y;
	} nextStep;

static nextStep movementMap[20][20];

class GameObject
{
public:
	~GameObject(){return;} //destructor
	double getXPos() {return xPos;}
	double getYPos() {return yPos;}
	int getCurrentHealth() {return currentHealth;}
	int getMaxHealth() {return maxHealth;}
	double getNextXPos() {return nextXPos;}
	double getNextYPos() {return nextYPos;}
	int getIsDead() {return isDead;}
	void setYPos(double y) {yPos = y; return;}
	void setXPos(double x) {xPos = x; return;}
	void setNextXPos(int x) {nextXPos = x;}
	void setNextYPos(int y) {nextYPos = y;}
	void collide(){return;}
	void setCurrentHealth(int health) {currentHealth = health; return;}
	void setMaxHealth(int health){maxHealth = health;}
	virtual void update(){};
	void die(){};
	virtual void draw(){

	};

protected:
	double xPos,yPos,nextXPos,nextYPos;
	int currentHealth,maxHealth,isDead,damage;
	int reset;
	int initialized;
};

class Enemy : public GameObject
{
public:
	Enemy()
	{
		maxHealth = 10; //10 sounds good...
		currentHealth = maxHealth;
		isDead = 0;
		reset=0;
		initialized=0;
	}

	void update()
	{

		if(initialized==0)
		{
			nextXPos = double(movementMap[int(xPos)][int(yPos)].x);
			nextYPos = double(movementMap[int(xPos)][int(yPos)].y);
			initialized=1;
		}
		double speed=.1;



		if((fabs(xPos - nextXPos) + fabs(yPos - nextYPos)) > .1 && reset == 0)
		{
			reset = 1;

		}


		if((fabs(xPos - nextXPos) + fabs(yPos - nextYPos)) < .2 && reset == 1)
		{
			xPos = nextXPos;
			yPos = nextYPos;
			nextXPos = double(movementMap[int(xPos)][int(yPos)].x);
			nextYPos = double(movementMap[int(xPos)][int(yPos)].y);
			reset = 0;

		}
		if(nextXPos > xPos)//moving right
		{
			xPos +=speed;
		}

		if(nextXPos < xPos) //moving left
		{
			xPos -=speed;
		}

		if(nextYPos > yPos) //moving up
		{
			yPos+=speed;
		}

		if(nextYPos < yPos) //moving up
		{
			yPos-=speed;
		}
	}


	void draw()
	{

			glBegin(GL_QUADS);

			glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  xPos+0.5, 0, yPos-0.5  );
			glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  xPos+0.5,  2, yPos-0.5 );
			glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( xPos-0.5,  2, yPos-0.5 );
			glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( xPos-0.5, 0, yPos-0.5 );

			glEnd();

			glBegin(GL_QUADS);
			glColor3f( 1.0, 0.0, 0.0 );glVertex3f(  xPos+0.5, 0.0, yPos + 0.5 );
			glColor3f( 0.0, 1.0, 0.0 ); glVertex3f(  xPos+0.5,  2, yPos + 0.5 );
			glColor3f( 0.0, 0.0, 1.0 );glVertex3f( xPos-0.5,  2, yPos + 0.5 );
			glColor3f( 1.0, 0.0, 1.0 );glVertex3f( xPos-0.5, 0, yPos + 0.5 );
			glEnd();

			// Purple side - RIGHT
			glBegin(GL_POLYGON);

			glColor3f( 1.0, 0.0, 0.0 );glVertex3f( xPos+0.5, 0, yPos-0.5 );
			glColor3f( 0.0, 1.0, 0.0 );glVertex3f( xPos+0.5,  2, yPos-0.5 );
			glColor3f( 0.0, 0.0, 1.0 );glVertex3f( xPos+0.5,  2,  yPos + 0.5 );
			glColor3f( 1.0, 0.0, 1.0 );glVertex3f( xPos+0.5, 0,  yPos + 0.5);
			glEnd();

			// Green side - LEFT
			glBegin(GL_POLYGON);

			glColor3f( 1.0, 0.0, 0.0 );glVertex3f( xPos-0.5, 0,  yPos + 0.5 );
			glColor3f( 0.0, 1.0, 0.0 );glVertex3f( xPos-0.5, 2,  yPos + 0.5 );
			glColor3f( 0.0, 0.0, 1.0 );glVertex3f( xPos-0.5,  2, yPos-0.5 );
			glColor3f( 1.0, 0.0, 1.0 );glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();

			// Blue side - TOP
			glBegin(GL_POLYGON);

			glColor3f( 1.0, 0.0, 0.0 );glVertex3f(  xPos+0.5,  2,  yPos + 0.5 );
			glColor3f( 0.0, 1.0, 0.0 );glVertex3f(  xPos+0.5,  2, yPos-0.5 );
			glColor3f( 0.0, 0.0, 1.0 );glVertex3f( xPos-0.5,  2, yPos-0.5 );
			glColor3f( 1.0, 0.0, 1.0 );glVertex3f( xPos-0.5,  2,  yPos + 0.5);
			glEnd();

			// Red side - BOTTOM
			glBegin(GL_POLYGON);

			glColor3f( 1.0, 0.0, 0.0 );glVertex3f(  xPos+0.5, 0, yPos-0.5 );
			glColor3f( 0.0, 1.0, 0.0 );glVertex3f(  xPos+0.5, 0, yPos +  0.5);
			glColor3f( 0.0, 0.0, 1.0 );glVertex3f( xPos-0.5, 0,  yPos + 0.5);
			glColor3f( 1.0, 0.0, 1.0 );glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();
		//glutSwapBuffers();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen




	//glutSwapBuffers();



	}
	int collide() {return damage;}
	void die() {isDead=1;}
};

class Defender : public GameObject
{
public:
	Defender()
	{
		xPos = 0;
		yPos = 0;
		maxHealth = 20; //10 sounds good...
		currentHealth = maxHealth;
		isDead = 0;
	}
	void update(){return;}
	void draw()
	{

		glBegin(GL_QUADS);
			//front side face
			glColor3f( 1.0, 0.0, 0.0 );
			glVertex3f(  xPos+0.5, 0, yPos-0.5 );
			glVertex3f(  xPos+0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();
			//  BACK
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.0, 0.0 );
			glVertex3f(  xPos+0.5, 0.0, yPos + 0.5 );
			glVertex3f(  xPos+0.5,  1, yPos + 0.5 );
			glVertex3f( xPos-0.5,  1, yPos + 0.5 );
			glVertex3f( xPos-0.5, 0, yPos + 0.5 );
			glEnd();

			//  RIGHT
			glBegin(GL_POLYGON);
			glColor3f(  1.0,  0.0,  1.0 );
			glVertex3f( xPos+0.5, 0, yPos-0.5 );
			glVertex3f( xPos+0.5,  1, yPos-0.5 );
			glVertex3f( xPos+0.5,  1,  yPos + 0.5 );
			glVertex3f( xPos+0.5, 0,  yPos + 0.5 );
			glEnd();

			//  LEFT
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.0,  1.0 );
			glVertex3f( xPos-0.5, 0,  yPos + 0.5 );
			glVertex3f( xPos-0.5, 1,  yPos + 0.5 );
			glVertex3f( xPos-0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();

			//  TOP
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  0.0,  1.0 );
			glVertex3f(  xPos+0.5,  1,  yPos + 0.5 );
			glVertex3f(  xPos+0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5,  1,  yPos + 0.5 );
			glEnd();

			// BOTTOM
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  0.0,  1.0 );
			glVertex3f(  xPos+0.5, 0, yPos-0.5 );
			glVertex3f(  xPos+0.5, 0, yPos +  0.5 );
			glVertex3f( xPos-0.5, 0,  yPos + 0.5 );
			glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();
	}
	int collide() {return damage;}
	void die() {isDead=1;}
};

class DefenderBase : public GameObject
{

public:
	DefenderBase()
	{
		xPos = 0;
		yPos = 0;
		maxHealth = 50; //10 sounds good...
		currentHealth = maxHealth;
		isDead = 0;
	}
	void draw(void)
	{
		glBegin(GL_QUADS);
			//front side face
			glColor3f( 1.0, 0.0, 1.0 );
			glVertex3f(  xPos+0.5, 0, yPos-0.5 );
		    glVertex3f(  xPos+0.5,  1, yPos-0.5 );
		    glVertex3f( xPos-0.5,  1, yPos-0.5 );
		    glVertex3f( xPos-0.5, 0, yPos-0.5 );

			glEnd();
			// BACK
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.0, 1.0 );
			glVertex3f(  xPos+0.5, 0.0, yPos + 0.5 );
			glVertex3f(  xPos+0.5,  1, yPos + 0.5 );
			glVertex3f( xPos-0.5,  1, yPos + 0.5 );
			glVertex3f( xPos-0.5, 0, yPos + 0.5 );
			glEnd();

			// RIGHT
			glBegin(GL_POLYGON);
			glColor3f(  1.0,  0.0,  0.0 );
			glVertex3f( xPos+0.5, 0, yPos-0.5 );
			glVertex3f( xPos+0.5,  1, yPos-0.5 );
			glVertex3f( xPos+0.5,  1,  yPos + 0.5 );
			glVertex3f( xPos+0.5, 0,  yPos + 0.5 );
			glEnd();

			// LEFT
			glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.0,  0.0 );
			glVertex3f( xPos-0.5, 0,  yPos + 0.5 );
			glVertex3f( xPos-0.5, 1,  yPos + 0.5 );
			glVertex3f( xPos-0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();

			// TOP
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  1.0,  1.0 );
			glVertex3f(  xPos+0.5,  1,  yPos + 0.5 );
			glVertex3f(  xPos+0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5,  1, yPos-0.5 );
			glVertex3f( xPos-0.5,  1,  yPos + 0.5 );
			glEnd();

			// BOTTOM
			glBegin(GL_POLYGON);
			glColor3f(   0.0,  1.0,  1.0 );
			glVertex3f(  xPos+0.5, 0, yPos-0.5 );
			glVertex3f(  xPos+0.5, 0, yPos +  0.5 );
			glVertex3f( xPos-0.5, 0,  yPos + 0.5 );
			glVertex3f( xPos-0.5, 0, yPos-0.5 );
			glEnd();

	}
	void update(){return;}
	void collide() {return;}
	void die() {isDead=1;}
};

class GameSquare
{
friend class Graph;
public:
	GameSquare(){};
	GameSquare(int x, int y)
	{
		location.x = x;
		location.y = y;
		previous.x = 0;
		previous.y = 0;
		dangerLevel = 0;
		tempDanger = 0;
		cumulativeDanger = 0;
	}

	int getDangerLevel(){return dangerLevel;}
	void addDanger(int danger) {dangerLevel+=danger;}
	double getXPos() {return location.x;}
	double getYPos() {return location.y;}
	bool isOpen() {return opened;}
	//bool isAdjacent(){return Adjacent;}
	bool isClosed(){return closed;}
//protected:
	struct coordinates{
		int x;
		int y;
	} location;
	struct nextCoordinates{
		int x;
		int y;
	} previous;
	bool opened;
	bool closed;
	int dangerLevel;
	int cumulativeDanger;
	int tempDanger;
	int distance;
};


class LandSquare : public GameSquare //we could implement other types, like forest, water, mountain, etc by inheriting from base class
{
public:
	LandSquare(){};
	LandSquare(int x, int y)
	{
		location.x = x;
		location.y = y;
		dangerLevel=1;
		cumulativeDanger=0;
		closed = false;
		opened = false;
		distance=0;
	}
	~LandSquare(){};


protected:

};


#endif
