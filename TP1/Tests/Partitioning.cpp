/*
 * Partioning.cpp
 */

#include "Partitioning.h"

//S(n,k) = S(n-1,k-1) + k S(n-1,k), se 1 < k < n
//S(n,k) = 1, se k=1 ou k=n
int s_recursive(int n,int k)
{
    if(k==1||n==1||k==n)
        return 1;
    else if(k>1 && k<n){
        return  s_recursive(n-1,k-1)+k*s_recursive(n-1,k);
    }
}

int s_dynamic(int n,int k)
{   
	return 1;
}


int b_recursive(int n)
{
    int sum=0;

    for(int k=1;k<=n;k++){
        sum+=s_recursive(n,k);
    }
	return sum;
}

int b_dynamic(int n)
{
	return 0;
}


