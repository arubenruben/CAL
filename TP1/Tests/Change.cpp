/*
 * Change.cpp
 */
#include <iostream>
using namespace std;

#include "Change.h"
#include <sstream>

string calcChange(int m, int numCoins, int *coinValues)
{
    if (m == 0)
    {
        return "";
    }
    ostringstream stringAux;

    int minCoins[m + 1];
    int lastCoins[m + 1];

    for (int i = 0; i <= m; i++)
    {
        if (i == 0)
        {
            minCoins[0] = 0;
        }
        else
        {
            minCoins[i] = 9999;
        }
        lastCoins[i] = -1;
    }

    for (int i = 0; i < numCoins; i++)
    {
        for (int k = 1; k <= m; k++)
        {
            if (coinValues[i] <= k &&
                (k - coinValues[i]) >= 0 &&
                (minCoins[k - coinValues[i]] + 1) < minCoins[k])
            {
                minCoins[k] = minCoins[k - coinValues[i]] + 1;
                lastCoins[k] = i;
            }
        }
    }
    for (int i = m; i > 0; i -= coinValues[lastCoins[i]])
    {
        if (lastCoins[i] == -1)
        {
            return "-";
        }
        else
        {
            stringAux << coinValues[lastCoins[i]] << ";";
        }
    }
    return stringAux.str();
}
