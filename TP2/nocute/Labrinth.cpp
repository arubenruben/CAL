/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
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

//em que 0 indica uma parede, 1 um espaço livre e 2 a saída

bool Labirinth::findGoal(int x, int y)
{
	//Se der overflow de memoria dar break
    std::cout<<"x:"<<x<<","<<"y:"<<y<<std::endl;

	if(x<0||y<0||x>9||y>9){
		return false;
	}
	std::cout<<"Value:"<<Labirinth::labirinth[x][y]<<std::endl;

	//Ja visitado
	if(Labirinth::visited[x][y]==true){
		return false;
	}else{
		//If not visited is set
		Labirinth::visited[x][y]=true;
	}
    if(Labirinth::labirinth[x][y]==2){
        std::cout<<"Encontrei Saida"<<std::endl;
        return true;
    }
	if(Labirinth::labirinth[x][y]==0){
		return false;	
	}
	//Recursive Step
	if(findGoal(x+1,y)==true){
		return true;
	}
	if(findGoal(x,y+1)==true){
		return true;
	}
	if(findGoal(x-1,y)==true){
		return true;
	}
	if(findGoal(x,y-1)==true){
		return true;
	}

	return false;
}


