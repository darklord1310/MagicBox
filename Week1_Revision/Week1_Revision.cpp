// Week1_Revision.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "windows.h"


#define ARROW_UP 			  72		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_DOWN  		  80		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_LEFT 			  75		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_RIGHT 		  77		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define KEY_DELETE  		  83		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_INSERT 	 		  82		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_PAGEUP  		  73		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_PAGEDOWN 		  81		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_HOME 			  71		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_END 			  79		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_ENTER			  13		// this is not a special key, only give 1 byte which is 13
#define KEY_BACKSPACE	 	   8		// this is not a special key, only give 1 byte which is 8
#define KEY_ESCAPE			  27	
#define MAX_BUFFER_SIZE		1024		
#define ESCAPECODE1			   0	
#define ESCAPECODE2			 224	
#define NORMALCODE			 255
#define CODE_ARROWUP		 0xE048
#define CODE_ARROWDOWN		 0xE050
#define CODE_ARROWLEFT		 0xE04B
#define CODE_ARROWRIGHT		 0xE04D
#define CODE_DELETE1		 0xE053
#define CODE_DELETE2		 0x0053
#define CODE_INSERT1		 0xE052
#define CODE_INSERT2		 0x0052
#define CODE_PAGEUP1		 0xE049
#define CODE_PAGEUP2		 0x0049
#define CODE_PAGEDOWN1		 0xE051
#define CODE_PAGEDOWN2	     0x0051
#define CODE_HOME1 			 0xE047	
#define CODE_HOME2			 0x0047
#define CODE_END1 			 0xE04F
#define CODE_END2 			 0x004F		
#define CODE_ENTER			 0xFF0D		
#define CODE_BACKSPACE	 	 0xFF08		
#define CODE_ESCAPE			 0xFF1B

typedef int Keycode;

using namespace std;

void printBox(int array[3][3]);
void UserInterface(int array[3][3]);
void IsMagicBox(int array[3][3]);
int checkForRepeativeValue(int IntegerEntered, int array[3][3], int row, int col);
char IsUserWantToPlayAgain();
void printNumberOrEmpty(int array[3][3], int row, int col);

int cursor = 1;

void _tmain(int argc, _TCHAR* argv[])
{
	char answer;

	do
	{
		int UserInput[3][3] = {};			// initialize the array
		UserInterface(UserInput);			// show the user interface to get input
		IsMagicBox(UserInput);				// check is it a magix box
		answer = IsUserWantToPlayAgain();	// Play again or not

	} while (answer != 'N');
	
	system("pause");
}


char IsUserWantToPlayAgain()
{
	char answer;
	cout << endl << endl;
	cout << "Do you want to play again? (Y/N) : ";
	cin >> answer;
	answer = toupper(answer);
	cout << endl;

	return answer;
}


void printBox(int array[3][3])
{
	cout << "			 _____________________" << endl;
	cout << "			|      |      |      |" << endl;
	cout << "			|      |      |      |" << endl;
	cout << "			|  ";
	printNumberOrEmpty(array, 0, 0); 
	cout << "   |   ";
	printNumberOrEmpty(array, 0, 1); 
	cout << "  |   ";
	printNumberOrEmpty(array, 0 , 2);
	cout << "  |" << endl;
	cout << "			|______|______|______|" << endl;
	cout << "			|      |      |      |" << endl;
	cout << "			|      |      |      |" << endl;
	cout << "			|  ";
	printNumberOrEmpty(array, 1, 0);
	cout << "   |   ";
	printNumberOrEmpty(array, 1, 1);
	cout << "  |   ";
	printNumberOrEmpty(array, 1, 2);
	cout << "  |" << endl;
	cout << "			|______|______|______|" << endl;
	cout << "			|      |      |      |" << endl;
	cout << "			|      |      |      |" << endl;
	cout << "			|  ";
	printNumberOrEmpty(array, 2, 0);
	cout << "   |   ";
	printNumberOrEmpty(array, 2, 1);
	cout << "  |   ";
	printNumberOrEmpty(array, 2, 2);
	cout << "  |" << endl;
	cout << "			|______|______|______|" << endl;
}


void printNumberOrEmpty(int array[3][3], int row, int col)
{
	if (array[row][col] == 0)
		cout << " ";
	else
		cout << array[row][col];

}


void refreshScreen(int array[3][3])
{
	system("CLS");
	printBox(array);
	cout << endl << endl << endl;
}

void UserInterface(int array[3][3])
{
	int row, col, isRepeative, IntegerEntered;
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			refreshScreen(array);
			cout << "Please enter any number you like in 1 to 9 to row " << row + 1 << " column " << col + 1 << ": ";
			cin >> IntegerEntered;
			cout << endl;

			isRepeative = checkForRepeativeValue(IntegerEntered, array, row, col);

			while ( IntegerEntered < 0 || IntegerEntered > 9 || isRepeative == 1)
			{
				refreshScreen(array);
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
	refreshScreen(array);

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

int get_character()
{
	return getch();
}


void put_character(int character)
{
	putchar(character);
}


Keycode IsSpecialKey(int key_code)
{
	int upper_byte, lower_byte;

	if (key_code == ESCAPECODE1 || key_code == ESCAPECODE2)
	{
		upper_byte = (key_code << 8);
		lower_byte = get_character();
		key_code = (upper_byte | lower_byte);
		if (key_code != CODE_ARROWUP && key_code != CODE_ARROWDOWN && key_code != CODE_ARROWLEFT && key_code != CODE_ARROWRIGHT &&
			key_code != CODE_DELETE1 && key_code != CODE_DELETE2 && key_code != CODE_INSERT1 && key_code != CODE_INSERT2 &&
			key_code != CODE_PAGEUP1 && key_code != CODE_PAGEUP2 && key_code != CODE_PAGEDOWN1 && key_code != CODE_PAGEDOWN2 &&
			key_code != CODE_HOME1   && key_code != CODE_HOME2   && key_code != CODE_END1 		&& key_code != CODE_END2)
			return 0;
		else
			return key_code;
	}
	else if (key_code == KEY_ENTER || key_code == KEY_BACKSPACE || key_code == KEY_ESCAPE)
	{
		upper_byte = (NORMALCODE << 8);
		lower_byte = key_code;
		key_code = (upper_byte | lower_byte);
		return key_code;
	}
	else
		return 0;
}

Keycode get_key_press()
{
	int	  key_code;

	key_code = get_character();
	return key_code;
}


/* To perform arrow right
*
*/
void handle_ARROWRIGHT()
{
	cursor+=7;

	// printBufferTill(user_input, cursor);
}




/* To perform arrow left
*
*/
void handle_ARROWLEFT()
{
	cursor-=7;

	// printBufferTill(user_input, cursor);
}


void printBufferTill(int length)
{
	int i;

	printf("\r");

	for (i = 0; i<length; i++)
	{
		
	}
}


void consoleClearLine()
{
	int i;

	printf("\r");
	for (i = 0; i<79; i++)
	{
		printf(" ");
	}
	printf("\r");
}



void InputInterface()
{
	int status, key_code;

	Keycode get_key_press();

	/*
	while (1)
	{
		key_code = get_key_press();
		status = IsSpecialKey(key_code);
		if (status != 0)		// status !=0 means special character input	
		{
			if (status == CODE_ENTER);
			{
				if (status == CODE_ARROWDOWN || status == CODE_ARROWUP || status == CODE_PAGEDOWN1 || status == CODE_PAGEDOWN2 ||
					status == CODE_PAGEUP1 || status == CODE_PAGEUP2);
				else
					strcpy(latest_input, "");
			}
			return status;
		}
		*/
}