/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve()
{
    int x=-1,y=-1;

    if (Sudoku::isComplete() == true)
    {
        return true;
    }

    if (Sudoku::findBestCell(x, y) == false)
    {
        return false;
    }

    for (int n = 1; n < 10; n++)
    {
        if (Sudoku::accepts(x, y, n))
        {
            Sudoku::setter(x, y, n);

            if (Sudoku::solve() == true)
            {
                return true;
            }
                //Do backtrack, we must undo
            else
            {
                Sudoku::undo(x, y, n);
            }
        }
    }

    return false;
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
//Return the best cell with least possibilities. If there is no possibilities return false ----> Backtrack
bool Sudoku::findBestCell(int &best_x, int &best_y){

    int bestX=-1;
    int bestY=-1;

    int minPossibleNumbers=9999;



    for(int x=0;x<9;x++){

        for(int y=0;y<9;y++){

            //Alread Filled
            if(this->numbers[x][y]!=0){
                continue;
            }

            int counterPossibleNumbersTemp=0;

            for(int n=1;n<10;n++){

                if(this->block3x3HasNumber[x][y][n]==false&&
                    this->columnHasNumber[y][n]== false&&
                    this->lineHasNumber[x][n]==false
                ){
                    counterPossibleNumbersTemp++;
                }
            }

            if(counterPossibleNumbersTemp<minPossibleNumbers){
                bestX=x;
                bestY=y;
                minPossibleNumbers=counterPossibleNumbersTemp;
            }
            //Greedy approach. 1 solution is always the optimal solution we can have
            if(minPossibleNumbers==1){
                best_x=bestX;
                best_y=bestY;
                return true;
            }


        }

    }

    if(bestX==-1||bestY==-1){
        return false;
    }

    best_x=bestX;
    best_y=bestY;

    return true;

}

bool Sudoku::accepts(int x, int y, int n)
{

    if (columnHasNumber[y][n] == false &&
        lineHasNumber[x][n] == false &&
        block3x3HasNumber[x / 3][y / 3][n] == false)
    {
        return true;
    }

    return false;
}

void Sudoku::setter(int x, int y, int n)
{

    Sudoku::countFilled++;
    Sudoku::columnHasNumber[y][n] = true;
    Sudoku::lineHasNumber[x][n] = true;
    Sudoku::block3x3HasNumber[x/3][y/3][n]=true;
    Sudoku::numbers[x][y] = n;

    return;
}

void Sudoku::undo(int x, int y, int n)
{
    Sudoku::countFilled--;
    Sudoku::columnHasNumber[y][n] = false;
    Sudoku::lineHasNumber[x][n] = false;
    Sudoku::block3x3HasNumber[x/3][y/3][n]=false;
    Sudoku::numbers[x][y] = 0;

    return;
}
