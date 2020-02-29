/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
	if(n==1){
		return 1;
	}else{
		return n*factorialRecurs(n-1);
	}
}

int factorialDinam(int n)
{
	int arrayAux[n];

	arrayAux[0]=1;

	for(int i=1;i<n;i++){
		arrayAux[i]=i*arrayAux[i-1];
	}
	
	return arrayAux[n-1];
}
