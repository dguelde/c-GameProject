//main for project, just a simple test right now

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <list>
#include <ctime>
#include "GameObjects.cpp"
#include "factory.cpp"
#include "pathfinder.cpp"
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))  



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

//  Globals...can't be helped with openGL, make static to confine here
static int th=0;       // Azimuth of view angle
static int ph=0;       // Elevation of view angle
static const int FPS = 60;
time_t lastTime;
GameObject* array[3];
GameSquare* gameBoard[20][20];//a 20 x 20 board..too big? too small?
//int mode=1;     // Dimension (1-4)
//double z=0;     // Z variable
//double w=1;     // W variable
//double dim=2;   // Dimension of orthogonal box


void initGameBoard(GameSquare* gameBoard[20][20], GameSquareFactory* factory)
{
	int index,index2;
	for(index=0;index<20;index++)
	{
		for(index2=0;index2<20;index2++)
		{
			gameBoard[index][index2] = factory->createSquare("Land");
			//std::cout << index <<" " <<  index2 << std::endl;
		}
		
	}
}

void timer(int v) {
  
  array[0]->update();
  glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
}

void initGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
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


void keyboard(unsigned char c, int x, int y)
{
	if (c==27) //escape ASCII value = 27
		{exit(0);}
	if (c==71) //escape ASCII value = 27
		{array[0]->update();}
	glutPostRedisplay();
}

void special(int key,int x,int y)
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
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON) //exit on right click
		{exit(0);}
	glutPostRedisplay();
}

void idle()
{
   //  Get elapsed (wall) time in seconds
  
   array[0]->update();
   
   //  Calculate spin angle 90 degrees/second
   //  Request display update
   glutPostRedisplay();
}




//GameObject* ptr;

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

   //glDepthRange(10,-10);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);


   //  Undo previous transformations
   glLoadIdentity();
   


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear screen
	glLoadIdentity();
	
	glRotated(ph,1,0,0);
	glRotated(th,0,1,0);
	//gluLookAt(10,10,10,10,0,10,1,0,0);

	int x;int y;int oldX=0; int oldY=0;
	//glTranslatef(10,0,10);
	glPushMatrix();
	glTranslatef(-10,0,-10);
	glClearColor(0,0,0,0);
	for (index=0;index<3;index++)
	{

		x = array[0]->getXPos();
		y = array[0]->getYPos();
		array[index]->draw();
		array[0]->update();
		glFlush();
		
		
		//std::cout << array[0]->getXPos();
		//glTranslatef(x-oldX,0,y-oldY);	
		//array[index]->draw();
		//oldX = x;
		//oldY = y;
		
	}
	
		
	
	
	
	//array[0]->draw(); //???????????????????
	//glTranslatef(1.5,0,-2);
	//array[1]->draw();
	//array[1]->draw();
	//glutSwapBuffers();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	//glutPostRedisplay();


	/*glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);//red,green,blue
		glVertex2f(-0.5,-0.5);//vertex in 2D, floats
		glColor3f(0,1,0);
		glVertex2f(0.5,-0.5);
		glColor3f(0,0,1);
		glVertex2f(0.0,0.5);
	glEnd();

	glutSwapBuffers();*/
	//ptr->draw();
}



void update(void)
{
	array[0]->update();
	glutPostRedisplay();
}



int main(int argc, char* argv[])
{
	//GameSquareFactory* gameSquareFactory = new GameSquareFactory;
	Factory factory = Factory();
	Graph graph = Graph();
	
	GameSquare *test = graph.getSquare(0,0);
	GameSquare *danger = graph.getSquare(0,1);
	danger->addDanger(10);
	danger = graph.getSquare(1,2);
	danger->addDanger(10);
	danger = graph.getSquare(2,0);
	danger->addDanger(10);
	danger = graph.getSquare(3,1);
	danger->addDanger(10);
	danger = graph.getSquare(4,1);
	danger->addDanger(10);
	danger = graph.getSquare(2,4);
	danger->addDanger(10);
	danger = graph.getSquare(3,7);
	danger->addDanger(10);
	danger = graph.getSquare(4,5);
	danger->addDanger(10);
	danger = graph.getSquare(5,9);
	danger->addDanger(10);
	danger = graph.getSquare(6,13);
	danger->addDanger(10);
	danger = graph.getSquare(7,17);
	danger->addDanger(10);
	danger = graph.getSquare(8,13);
	danger->addDanger(10);
	danger = graph.getSquare(9,19);
	danger->addDanger(10);
	danger = graph.getSquare(10,15);
	danger->addDanger(10);
	danger = graph.getSquare(9,14);
	danger->addDanger(10);
	danger = graph.getSquare(5,9);
	danger->addDanger(10);

	graph.pathFinder(10,10);
	int nextX;
	int nextY;

	while (test->getXPos() != 10 || test->getYPos()!=10)
	{
		nextX = test->previous.x;
		nextY = test->previous.y;
		std::cout << nextX << "," << nextY << std::endl;
		test = graph.getSquare(nextX,nextY);
	}

	
	//std::cout <<graph.squares.size() << std::endl;
	
	//graph->buildWorld();
	
	
	
	//GameObject* array[3];
	
	array[0] = factory.createObject("Enemy");
	array[0]->setXPos(0);array[0]->setYPos(10);
	array[0]->setNextXPos(1);array[0]->setNextYPos(11);
	//array[0]->setNewXPos(1);
	array[1] = factory.createObject("Defender");
	array[1]->setXPos(1);array[1]->setYPos(1);
	array[2] = factory.createObject("DefenderBase");
	array[2]->setXPos(10);array[2]->setYPos(10);
	//std::cout << array[0]->getCurrentHealth() << std::endl;
	//std::cout << array[1]->getCurrentHealth() << std::endl;
	//std::cout << array[2]->getCurrentHealth() << std::endl;

	
	
	
	

	//opengl stuff, test rendering game objects...
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);


	glutCreateWindow("Project Practice OpenGL");
	initGL(640,480);
	
	//glutIdleFunc(update);
	glutIdleFunc(update); 
	//glutFullScreen();
	//glutTimerFunc(100,timer,0);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMainLoop();
	

	
}


