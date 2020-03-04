/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;

Labirinth::Labirinth(int values[10][10])
{
    Labirinth::initializeVisited();
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

void Labirinth::printLabirinth()
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

    if (x > 9 || y > 9 || x < 0 || y < 0)
    {
        return false;
    }

    if (Labirinth::labirinth[x][y] == 2)
    {
        std::cout << "Encontrei Solucao na posicao x:" << x << "y:" << y << std::endl;
        return true;
    }
    //Nao posso testar para violar segmento em x=9
    if (x > 8 || y > 8 || x < 1 || y < 1)
    {
        return false;
    }

    Labirinth::visited[x][y] = true;

    //So entro no caso de teste se ele nao for uma parede, nao vou esbarrar contra uma parede
    if (Labirinth::labirinth[x + 1][y] != 0 && Labirinth::visited[x + 1][y] == false)
    {
        if (findGoal(x + 1, y))
            return true;
    }
    if (Labirinth::labirinth[x][y + 1] != 0 && Labirinth::visited[x][y + 1] == false)
    {
        if (findGoal(x, y + 1))
            return true;
    }
    if (Labirinth::labirinth[x - 1][y] != 0 && Labirinth::visited[x - 1][y] == false)
    {
        if (findGoal(x - 1, y))
            return true;
    }
    if (Labirinth::labirinth[x][y - 1] != 0 && Labirinth::visited[x][y - 1] == false)
    {
        if (findGoal(x, y - 1))
            return true;
    }

    return false;
}
