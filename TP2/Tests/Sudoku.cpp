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
int **Sudoku::getNumbers()
{
	int **ret = new int *[9];

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
	int x = -1, y = -1;

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

bool Sudoku::findBestCell(int &best_i, int &best_j)
{

	int minSolution = 999;
	int bestI = -1, bestJ = -1;
	int **board = Sudoku::getNumbers();

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
            if(board[x][y]!=0)
                continue;

			int counterSolutions = 0;

			for (int n = 1; n < 10; n++)
			{
				//Div integer
				if (Sudoku::lineHasNumber[x][n] == false &&
					Sudoku::columnHasNumber[y][n] == false &&
					Sudoku::block3x3HasNumber[x / 3][y / 3][n]==false)
				{
					counterSolutions++;
				}
			}
			if(counterSolutions==0){
                return false;
			}
			if (counterSolutions < minSolution)
			{
				minSolution = counterSolutions;
				bestI = x;
				bestJ = y;
				//Gready Approach: I never get better than a unique solution
				if (minSolution == 1)
				{
					best_i = bestI;
					best_j = bestJ;
					return true;
				}
			}
		}
	}

	if (bestI == -1 && bestJ == -1)
	{
		return false;
	}

	best_i = bestI;
	best_j = bestJ;

	return true;
}

bool Sudoku::accepts(int i, int j, int n)
{

	if (columnHasNumber[j][n] == false &&
		lineHasNumber[i][n] == false &&
		block3x3HasNumber[i / 3][j / 3][n] == false)
	{
		return true;
	}

	return false;
}
void Sudoku::setter(int i, int j, int n)
{

	Sudoku::countFilled++;
	Sudoku::columnHasNumber[j][n] = true;
	Sudoku::lineHasNumber[i][n] = true;
	Sudoku::block3x3HasNumber[i/3][j/3][n]=true;
	Sudoku::numbers[i][j] = n;

	return;
}

void Sudoku::undo(int i, int j, int n)
{
	Sudoku::countFilled--;
	Sudoku::columnHasNumber[j][n] = false;
	Sudoku::lineHasNumber[i][n] = false;
    Sudoku::block3x3HasNumber[i/3][j/3][n]=false;
	Sudoku::numbers[i][j] = 0;

	return;
}
