//this .cpp file and its functions encapsulate the openGL functions, calls, etc.

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <list>
#include <ctime>
#include "gameObjects.cpp"
#include "factory.cpp"
#include "pathfinder.cpp"
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))




#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Globals...can't be helped with openGL, make static to confine here

static int th=0;       // Azimuth of view angle
static int ph=0;       // Elevation of view angle
static const int FPS = 60;


GameObject* gameObjectArray[7]; //holds game objects so update() can find them

void initGL(int Width, int Height)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();				// Reset The Projection Matrix
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
  glMatrixMode(GL_MODELVIEW);

}

double getDistance(int fromX, int fromY, int toX, int toY)
{
	double distance = sqrt(pow(abs(toY - fromY),2)+pow(abs(toX-fromX),2));

	return distance;
}


void keyboard(unsigned char c, int x, int y) //watches for keyboard input (esc = quit)
{
	if (c==27) //escape ASCII value = 27
		{exit(0);}
	glutPostRedisplay();
}

void special(int key,int x,int y) //watches for special key presses (arrow keys rotate game board)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) //monitors for mouse input (right click = exit)
{
	if(button == GLUT_RIGHT_BUTTON) //exit on right click
		{exit(0);}
	glutPostRedisplay();
}

void render()
{
	int width, height, index, index2;
	int dim=20;

	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
    glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear screen
	//glLoadIdentity();
	glRotated(90,1,0,0);
	glRotated(90,0,1,0);
	glRotated(ph,0,0,1);
	glRotated(th,0,1,0);


	int x;int y;int oldX=0; int oldY=0;
	glPushMatrix();
	glTranslatef(-10,0,-10);
	glClearColor(0,0,0,0);
	glBegin(GL_POLYGON); //a simple board surface, graphical only,
			glColor3f(   1.0,  1.0,  1.0 );
			glVertex3f(  -.5, 0, -.5 );
			glVertex3f(  19.5, 0, -.5);
			glVertex3f( 19.5, 0, 19.5);
			glVertex3f( -.5, 0, 19.5 );
			glEnd();
	for (index=0;index<7;index++) //iterate through the gameObject gameObjectArray and draw
	{
		gameObjectArray[index]->draw();
	}
	glPopMatrix();//undo transformations
	glFlush();
	glutSwapBuffers();
}

void update(void)
{
	for (int index=0;index<7;index++)
	{
		gameObjectArray[index]->update();
	}
	glutPostRedisplay();
}

int Draw(int argc, char* argv[], int defenderYCoord[], int defenderXCoord[])
{

	Factory factory = Factory();
	Graph graph = Graph();



	for (int index = 1;index<5;index++) //danger level for each game square
	{

	for(int index2=0;index2<20;index2++)
	{
		for(int index3=0;index3<20;index3++)
		{

			graph.getSquare(index2,index3)->addDanger(int(27/getDistance(index2,index3,defenderXCoord[index],defenderYCoord[index])));
		}
	}
	}


	graph.pathFinder(defenderXCoord[0],defenderYCoord[0]); //AI pathing for whole gameboard, from any square to coordinates of defender base


	gameObjectArray[0] = factory.createObject("DefenderBase");
	gameObjectArray[0]->setXPos(defenderXCoord[0]);gameObjectArray[0]->setYPos(defenderYCoord[0]);
	for (int index = 1;index<5;index++)
	{
		gameObjectArray[index] = factory.createObject("Defender");
		gameObjectArray[index]->setXPos(defenderXCoord[index]);gameObjectArray[index]->setYPos(defenderYCoord[index]);
	}

	gameObjectArray[5] = factory.createObject("Enemy"); //just make 2 enemies
	gameObjectArray[5]->setXPos(19);
	gameObjectArray[5]->setYPos(19);
	gameObjectArray[6] = factory.createObject("Enemy");
	gameObjectArray[6]->setXPos(0);
	gameObjectArray[6]->setYPos(0);



	//opengl stuff
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("C++ Defender");
	initGL(640,480);
	glutIdleFunc(update);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMainLoop();
}
