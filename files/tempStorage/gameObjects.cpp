

Enemy::Enemy(){
	xPos = 0; 
	yPos = 0;
	maxHealth = 10; //10 sounds good...
	currentHealth = maxHealth;
	isDead = 0;
}

void Enemy::draw()
{
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
		//bottom face
		glvertex3f(-.5,0,.5)
		glvertex3f(.5,0,.5);
		glvertex3f(.5,0,-.5);
		glvertex3f(-.5,0,-.5);
		//right face
		glvertex3f(.5,0,.5);
		glvertex3f(.5,0,-.5);
		glvertex3f(.5,1,-.5);
		glvertex3f(.5,1,.5);
		//back face
		glvertex3f(.5,0,-.5);
		glvertex3f(-.5,0,-.5);
		glvertex3f(-.5,1,-.5);
		glvertex3f(.5,1,-.5);
		//left face
		glvertex3f(-.5,0,.5);
		glvertex3f(-.5,0,-.5);
		glvertex3f(-.5,1,-.5);
		glvertex3f(-.5,1,.5);
		//front face
		glvertex3f(-.5,0,.5);
		glvertex3f(.5,0,.5);
		glvertex3f(.5,1,.5);
		glvertex3f(-.5,1,.5);
		//top face
		glvertex3f(-.5,1,.5)
		glvertex3f(.5,1,.5);
		glvertex3f(.5,1,-.5);
		glvertex3f(-.5,1,-.5);
}


float Enemy::getXPos() {return xPos;}
float Enemy::getYPos() {return yPos;}
int Enemy::getCurrentHealth() {return currentHealth;}
int Enemy::getMaxHealth() {return maxHealth;}
float Enemy::getNextXPos() {return nextXPos;}
float Enemy::getNextYPos() {return nextYPos;}
int Enemy::getIsDead() {return isDead;}
void Enemy::setXPos(float x); {xPos = x; return;}
void Enemy::setYpos(float y); {yPos = y; return;}
int Enemy::setCurrentHealth(int health); {currentHealth = health; return;}
void Enemy::setMaxHealth(int newMaxHealth); (maxHealth = newMaxHealth; return;)
int Enemy::collide() {return damage;}
void Enemy::die() {isDead=1;}
int Enemy::getIsDead() {return isDead;}