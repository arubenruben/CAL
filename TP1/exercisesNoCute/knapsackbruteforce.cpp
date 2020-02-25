#include <iostream>
#include <vector>
//IMPORTANT: THIS ALGORITHM WOKRS WITH A FINITE NUMBER OF CASES DIFFERENT FROM THE ONE IN THE SLIDES
std::vector<int> aux;
std::vector<std::vector<int>> matrix;

int knapSackBruteForce(int currentCapacity, int *wt, int *val, int treeLevel)
{
    if (treeLevel == 0 || currentCapacity == 0)
    {
        if (!aux.empty())
        {
            matrix.push_back(aux);
        }
        return 0;
    }

    //Not Yet at the end
    if (wt[treeLevel - 1] > currentCapacity)
    {
        return knapSackBruteForce(currentCapacity, wt, val, treeLevel - 1);
    }
    else
    {
        std::vector<int> auxLocal(aux);

        //In
        aux.push_back(treeLevel - 1);
        int valIn = val[treeLevel - 1] + knapSackBruteForce(currentCapacity - wt[treeLevel - 1], wt, val, treeLevel - 1);

        //Out
        aux.clear();

        for (int i = 0; i < auxLocal.size(); i++)
        {
            aux.push_back(auxLocal.at(i));
        }

        int valOut = knapSackBruteForce(currentCapacity, wt, val, treeLevel - 1);

        if (valIn > valOut)
        {
            aux.push_back(treeLevel - 1);
            return valIn;
        }
        else
        {
            return valOut;
        }
    }
}

int main()
{

    int val[] = {4, 5, 10, 10, 11, 13};
    int wt[] = {3, 4, 7, 7, 8, 9};
    int W = 17;
    int n = sizeof(val) / sizeof(val[0]);
    std::cout << knapSackBruteForce(W, wt, val, n) << std::endl;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.at(i).size(); j++)
        {
            std::cout << matrix.at(i).at(j) << ",";
        }
        std::cout << std::endl;
    }
    return 0;
}