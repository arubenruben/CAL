/*
 * Factorial.cpp
 */

#include <iostream>
#include <vector>
#include "Factorial.h"

int factorialRecurs(int n)
{
    if(n==1){
        return 1;

    } else if (n>=1){
        return  n *factorialRecurs(n-1);
    }
}

int factorialDinam(int n)
{
    std::vector <int> vectorAux;

    vectorAux.push_back(1);

    for(int i=1;i<=n;i++) {
        vectorAux.push_back(i * vectorAux[i - 1]);
    }
    std::cout << vectorAux[n];

	return vectorAux[n];
}
