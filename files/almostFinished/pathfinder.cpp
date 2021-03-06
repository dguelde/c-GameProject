

#ifndef PATHFINDER
#define PATHFINDER


#include <iostream>
#include <vector>
#include "gameObjects.cpp"

class Graph //I should have split this into .h and .cpp files, but.....
{
public:
	Graph(){
		for(int index=0;index<20;index++)
		{
			for(int index2=0;index2<20;index2++)
			{
				squares.push_back(new LandSquare(index,index2));
			}
		}
	};

	GameSquare* getSquare(int x, int y) //a helper function to get the node at (x,y),
	{
		if( x<0 || x>=20 || y<0 || y >= 20) //if outside map
		{
			return nullNode;
		}
		int length = squares.size();
		for(int index=0;index<length;index++)
		{
			if(squares[index]->location.x == x && squares[index]->location.y == y)
			{
				return squares[index];
			}
		}
	}

	std::vector<GameSquare*> getAdjacent(GameSquare* center) //returns a vector of valid nodes surrounding (x,y) (ensures we don't go off the map)
	{
		int x = center->location.x;
		int y = center->location.y;
		std::vector<GameSquare*> adjacentSquares;
		if(x>=0 && x<20 && y-1>= 0 && y-1<20) adjacentSquares.push_back(getSquare(x,y-1));
		if(x>=0 && x < 20 && y >= 0 && y < 20) adjacentSquares.push_back(getSquare(x,y+1));
		if(x-1>=0 && x-1 < 20 && y >= 0 && y < 20) adjacentSquares.push_back(getSquare(x-1,y));
		if(x+1>=0 && x+1< 20 && y >= 0 && y < 20) adjacentSquares.push_back(getSquare(x+1,y));

		return adjacentSquares;
	}

	bool openedQueueIsEmpty()
	{
		bool found = false;

		for(int index5=0;index5<squares.size();index5++)
		{
			if(squares[index5]->opened == true)
			{
				found = true;
			}
			else
			{
			}

		}

		return found;
	}


	void pathFinder(int x, int y)
	{
		int max = 999999999;
		int temp;
		int nextX,nextY;
		GameSquare* goal = getSquare(x,y);
		GameSquare * current;
		GameSquare *next;
		GameSquare *previous;
		std::vector<GameSquare*> adjacentList;
		int squaresSize = squares.size();
		goal->opened = false;
		goal->closed = true;
		adjacentList.clear();
		adjacentList = getAdjacent(goal);
		movementMap[  goal->location.x ][ goal->location.y  ].x=goal->location.x;
		movementMap[  goal->location.x ][ goal->location.y  ].y=goal->location.y;
		for(int index=0;index<adjacentList.size();index++)
		{
			adjacentList[index]->previous.x = goal->location.x; //so we can remember the path to goal
			adjacentList[index]->previous.y = goal->location.y;
			movementMap[  adjacentList[index]->location.x ][ adjacentList[index]->location.y  ].x=goal->location.x;
			movementMap[  adjacentList[index]->location.x ][ adjacentList[index]->location.y  ].y=goal->location.y;
			adjacentList[index]->opened = true;
			adjacentList[index]->closed = false;
			adjacentList[index]->cumulativeDanger = adjacentList[index]->dangerLevel; //no extra danger to move to goal
			adjacentList[index]->tempDanger = adjacentList[index]->dangerLevel;
		}
		while(openedQueueIsEmpty()==1)
		{

			//get opened square w/ lowest cumulativeDanger
			temp = max; //used to find lowest total danger
			int tempDanger = 0;
			for (int index=0;index<squaresSize;index++)//next square to close will be min(danger level known so far)
			{

				if(squares[index]->opened == true)
				{

					if(squares[index]->tempDanger <= temp)
					{
						current = squares[index];
						temp = current->tempDanger;
					}
				}
			}
			previous = getSquare(current->previous.x,current->previous.y);
			current->opened = false;
			current->closed = true;
			current->cumulativeDanger = current->tempDanger+1; //locked in, closed, path is final, cumulative damage is final
			adjacentList.clear();
			adjacentList=getAdjacent(current);
			if(adjacentList.size() >0 )
			{
				for(int index=0;index<adjacentList.size();index++)
				{
					if(adjacentList[index]!= 0x0)
					{
						if(adjacentList[index]->opened == true) //recheck, maybe a better path
						{
							int tempDanger = adjacentList[index]->dangerLevel + current->cumulativeDanger;
							if(tempDanger < adjacentList[index]->tempDanger) //update path, this one is better
							{
								adjacentList[index]->previous.x = current->location.x;
								adjacentList[index]->previous.y = current->location.y;
								movementMap[  adjacentList[index]->location.x ][ adjacentList[index]->location.y  ].x=current->location.x;
								movementMap[  adjacentList[index]->location.x ][ adjacentList[index]->location.y  ].y=current->location.y;
								adjacentList[index]->tempDanger = tempDanger;
							}
						}
						else if(adjacentList[index]->closed == false)
						{
							adjacentList[index]->opened = true;
							adjacentList[index]->closed = false;
							adjacentList[index]->previous.x = current->location.x;
							adjacentList[index]->previous.y = current->location.y;
							movementMap[  adjacentList[index]->location.x ][ adjacentList[index]->location.y  ].x=current->location.x;
							movementMap[  adjacentList[index]->location.x ][ adjacentList[index]->location.y  ].y=current->location.y;
							adjacentList[index]->tempDanger = adjacentList[index]->dangerLevel + current->cumulativeDanger;
						}
					}
				}
			}
		}

	}

	std::vector<GameSquare*> squares;
	GameSquare* nullNode = nullptr;
	int height = 20;
	int width = 20;
};

#endif
