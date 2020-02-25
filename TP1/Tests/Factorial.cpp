/*
 * Factorial.cpp
 */

#include <iostream>
#include <vector>
#include <exception>
#include "Factorial.h"


//FAT N = N * FAT N -1
//Temp: O(n)
//Space:O(n)
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
        try {
            vectorAux.at(i);
        }catch(std::exception &e){
            vectorAux.push_back(i * vectorAux[i - 1]);
        }
    }
    std::cout << vectorAux[n];

	return vectorAux[n];
}
