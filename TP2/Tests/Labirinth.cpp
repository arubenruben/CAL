/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
            labirinth[i][j] = values[i][j];
		    visited[i][j]=false;
		}
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

/*
 *
 *
    em que 0 indica uma parede, 1 um
    espaço livre e 2 a saída.
 */
bool Labirinth::findGoal(int x, int y)
{
    if(solutionAt(x,y))
        return true;

    if(promising(x+1,y)){

        if(findGoal(x+1,y))
            return true;
    }
    if(promising(x-1,y)){

        if(findGoal(x-1,y))
            return true;
    }
    if(promising(x,y+1)) {

        if (findGoal(x, y + 1))
            return true;
    }
    if(promising(x,y-1)) {
        if (findGoal(x, y - 1))
            return true;
    }
    return false;
}


bool Labirinth::solutionAt(const int x,const int y){
    if(x<0||x>9){
        return false;
    }
    if(y<0||y>9){
        return false;
    }
    if(this->labirinth[x][y]==2){
        return true;
    }
    return false;
}
bool Labirinth::promising(const int x, const int y){
    if(x<0||x>9){
        return false;
    }
    if(y<0||y>9){
        return false;
    }
    if(this->visited[x][y]==true){
        return false;
    }
    if(this->labirinth[x][y]==1||this->labirinth[x][y]==2){
        this->visited[x][y]=true;
        return  true;
    }
    return false;
}


