/*
 * Sum.cpp
 */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string calcSum(int* sequence, int size)
{
    ostringstream aux;

    int matrix[size][size];

    for (int j = 0; j < size; j++)
    {
        matrix[0][j] = sequence[j];
    }

    for (int i = 1; i < size; i++)
    {

        for (int j = 0; j < size - i; j++)
        {
            matrix[i][j] = matrix[i - 1][j] + sequence[j + i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        int minimum = 999;
        int index = 0;
        for (int j = 0; j < size - i; j++)
        {
            if (matrix[i][j] < minimum)
            {
                minimum = matrix[i][j];
                index = j;
            }
            if (j == size - i - 1)
            {
                aux << minimum << "," << index << ";";
            }
        }
    }

    return aux.str();
}

