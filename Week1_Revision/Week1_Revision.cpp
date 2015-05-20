// Week1_Revision.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"

using namespace std;

void UserInterface(int array[3][3]);
void IsMagicBox(int array[3][3]);
int checkForRepeativeValue(int IntegerEntered, int array[3][3], int row, int col);


void _tmain(int argc, _TCHAR* argv[])
{

	int UserInput[3][3] = {};


	UserInterface(UserInput);		// show the user interface to get input
	IsMagicBox(UserInput);			// check is it a magix box

	system("pause");
}


void UserInterface(int array[3][3])
{
	int row, col, isRepeative, IntegerEntered;
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			cout << "Please enter any number you like in 1 to 9 to row " << row + 1 << " column " << col + 1 << ": ";
			cin >> IntegerEntered;
			cout << endl;

			isRepeative = checkForRepeativeValue(IntegerEntered, array, row, col);

			while ((IntegerEntered < 0 && IntegerEntered > 9) || isRepeative == 1)
			{
				cout << "Please re-enter a valid value! : ";
				cin >> IntegerEntered;
				isRepeative = checkForRepeativeValue(IntegerEntered, array, row, col);
			}

			array[row][col] = IntegerEntered;
		}
	}
}



int checkRow(int array[3][3])
{
	int sum[3] = { 0 };
	int row, col, sum_result = 0;

	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			sum[sum_result] = sum[sum_result] + array[row][col];
			if (col == 2)
				sum_result++;
		}
	}

	if (sum[0] == 15 && sum[1] == 15 && sum[2] == 15)
		return 1;
	else
		return 0;
}


int checkColumn(int array[3][3])
{
	int sum[3] = { 0 };
	int row, col, sum_result = 0;

	for (col = 0; col < 3; col++)
	{
		for (row = 0; row < 3; row++)
		{
			sum[sum_result] = sum[sum_result] + array[row][col];
			if (row == 2)
				sum_result++;
		}
	}

	if (sum[0] == 15 && sum[1] == 15 && sum[2] == 15)
		return 1;
	else
		return 0;
}



int checkDiagonal(int array[3][3])
{
	int sum[2] = { 0 };
	int row, col = 0, sum_result = 0;

	for (row = 0; row < 3; row++)
	{
		sum[sum_result] = sum[sum_result] + array[row][col];
		col++;
	}

	sum_result++;

	for (int i = 0; i < 3; i++)
	{
		col--;
		row--;
		sum[sum_result] = sum[sum_result] + array[row][col];
	}

	if (sum[0] == 15 && sum[1] == 15)
		return 1;
	else
		return 0;
}

void IsMagicBox(int array[3][3])
{
	if (checkRow(array) == 1 && checkColumn(array) == 1 && checkDiagonal(array) == 1)
		cout << "Congratulations! It is a magic box. Thank you for playing!" << endl;
	else
		cout << "Sorry, it is not a magic box, better luck next time!" << endl << endl;
}

int checkForRepeativeValue(int IntegerEntered, int array[3][3], int row, int col)
{
	if (row == 0 && col == 0)
		return 0;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (IntegerEntered == array[j][i])
				return 1;
		}
	}
	return 0;
}