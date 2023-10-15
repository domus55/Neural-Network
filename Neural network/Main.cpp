#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include "Board.h"
#include "Neuron.h"
#include "NeuralNetworkBot.h"
#include "gtest/gtest.h"

using namespace std;

Board board;

NeuralNetworkBot bot;

void stop();
void bot1(char);
void bot2(char);
void bot3(char);
void bot4(char);
void neuralNetwork(char);

bool stopp = false; // usunac
bool stopp2 = false; //usunac

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

	srand(time(NULL));
	int O_buffor, X_buffor;
	typedef void(*bot)(char);
	bot O = bot1;
	bot X = bot1;

	cout << "Hints: \n" <<
		"1. Use 'o' and 'p' keys to see actual game \n" <<
		"2. The neural network has a cross mark \n" <<
		"3. Easy opponent is really difficult to beat for neural network, because it chooses random fields \n";
	Sleep(1000);
	cout << "Click any key \n";
	_getwch();
	system("cls");


	cout << "Chose neural network opponent difficulty: " << endl
		<< "1. easy" << endl
		<< "2. medium" << endl
		<< "3. hard" << endl
		<< "4. almost impossible" << endl;
	O_buffor = _getwch();


	X = neuralNetwork;

	switch (O_buffor)
	{
	case 49: O = bot1;  break;
	case 50: O = bot2;  break;
	case 51: O = bot3;  break;
	case 52: O = bot4;  break;
	}

	for (;;)
	{
		O('o');
		stop();
		board.Wygrana();

		X('x');
		stop();
		board.Wygrana();
	}

}

///<summary>
///This bot puts sign on a random empty field
///</summary>
void bot1(char symboll)
{
	int symbol;
	if (symboll == 'o') symbol = 1;
	else symbol = 2;


	bool end;
	do {
		int a = rand() % 3;
		int b = rand() % 3;
		end = false;

		if (board.field[a][b] == 0) {
			board.field[a][b] = symbol;
			end = true;
		}
	} while (!end);
}

///<summary>
///This bot assgns value to all fields and puts sign on the most valuable one.
///If there are few fields with the same value, it chooses a random one
///</summary>
void bot2(char symboll)
{
	int randField;
	int mostValuableField;
	int amountOfBestFields = 0;
	int x[9];

	int symbol;
	if (symboll == 'o') symbol = 1;
	else symbol = 2;

	x[4] = 11;
	x[0] = 6;
	x[2] = 6;
	x[6] = 6;
	x[8] = 6;
	x[1] = 4;
	x[3] = 4;
	x[5] = 4;
	x[7] = 4;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board.field[i][j] != 0) { x[i * 3 + j] = 0; }
		}
	}

	mostValuableField = x[0];
	for (int i = 1; i < 9; i++)
	{
		if (x[i] >= mostValuableField) { mostValuableField = x[i]; }
	}

	for (int i = 0; i < 9; i++)
	{
		if (x[i] == mostValuableField) { amountOfBestFields++; }
	}
	randField = rand() % amountOfBestFields;

	int *bestFields = new int[amountOfBestFields];

	int b = 0;
	int n = 0;

	for (int i = 0; i < 9; i++)
	{
		if (x[i] == mostValuableField) { bestFields[b] = i; b++; }
	}

	n = bestFields[randField];

	board.field[n / 3][n % 3] = symbol;
}

///<summary>
///This bot assgns value to all fields and puts sign on the most valuable one.
///Fields can change value if there are other marks around it.
///If there are few fields with the same value, it chooses a random one
///</summary>
void bot3(char symboll)
{
	int randomField;
	int mostValuableField;
	int amountOfBestFields = 0;
	int x[9];

	int symbol;
	if (symboll == 'o') symbol = 1;
	else symbol = 2;

	x[4] = 11;
	x[0] = 6;
	x[2] = 6;
	x[6] = 6;
	x[8] = 6;
	x[1] = 4;
	x[3] = 4;
	x[5] = 4;
	x[7] = 4;

	if (board.field[0][0] == symbol) { x[1] += 4; x[2] += 2; x[3] += 4; x[6] += 4; }
	if (board.field[0][2] == symbol) { x[0] += 4; x[1] += 2; x[5] += 4; x[8] += 4; }
	if (board.field[2][0] == symbol) { x[0] += 4; x[3] += 2; x[7] += 4; x[8] += 4; }
	if (board.field[2][2] == symbol) { x[2] += 4; x[5] += 2; x[6] += 4; x[7] += 4; }

	if (board.field[0][0] == symbol && board.field[1][0] == symbol) { x[6] += 20; }
	if (board.field[0][1] == symbol && board.field[1][1] == symbol) { x[7] += 20; }
	if (board.field[0][2] == symbol && board.field[1][2] == symbol) { x[8] += 20; }

	if (board.field[1][0] == symbol && board.field[2][0] == symbol) { x[0] += 20; }
	if (board.field[1][1] == symbol && board.field[2][1] == symbol) { x[1] += 20; }
	if (board.field[1][2] == symbol && board.field[2][2] == symbol) { x[2] += 20; }

	if (board.field[0][0] == symbol && board.field[0][1] == symbol) { x[2] += 20; }
	if (board.field[1][0] == symbol && board.field[1][1] == symbol) { x[5] += 20; }
	if (board.field[2][0] == symbol && board.field[2][1] == symbol) { x[8] += 20; }

	if (board.field[0][1] == symbol && board.field[0][2] == symbol) { x[0] += 20; }
	if (board.field[1][1] == symbol && board.field[1][2] == symbol) { x[3] += 20; }
	if (board.field[2][1] == symbol && board.field[2][2] == symbol) { x[6] += 20; }
	
	if (board.field[0][0] == symbol && board.field[2][0] == symbol) { x[3] += 20; }
	if (board.field[0][1] == symbol && board.field[2][1] == symbol) { x[4] += 20; }
	if (board.field[0][2] == symbol && board.field[2][2] == symbol) { x[5] += 20; }

	if (board.field[0][0] == symbol && board.field[0][2] == symbol) { x[1] += 20; }
	if (board.field[1][0] == symbol && board.field[1][2] == symbol) { x[4] += 20; }
	if (board.field[2][0] == symbol && board.field[2][2] == symbol) { x[7] += 20; }
	
	if (board.field[0][0] == symbol && board.field[1][1] == symbol) { x[8] += 20; }
	if (board.field[0][2] == symbol && board.field[1][1] == symbol) { x[6] += 20; }
	if (board.field[2][0] == symbol && board.field[1][1] == symbol) { x[2] += 20; }
	if (board.field[2][2] == symbol && board.field[1][1] == symbol) { x[0] += 20; }


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board.field[i][j] != 0) { x[i * 3 + j] = 0; }
		}
	}

	mostValuableField = x[0];
	for (int i = 1; i < 9; i++)
	{
		if (x[i] >= mostValuableField) { mostValuableField = x[i]; }
	}

	for (int i = 0; i < 9; i++)
	{
		if (x[i] == mostValuableField) { amountOfBestFields++; }
	}
	randomField = rand() % amountOfBestFields;

	int *bestFields = new int[amountOfBestFields];

	int b = 0;
	int n = 0;

	for (int i = 0; i < 9; i++)
	{
		if (x[i] == mostValuableField) { bestFields[b] = i; b++; }
	}

	n = bestFields[randomField];

	board.field[n / 3][n % 3] = symbol;
}


///<summary>
///This bot assgns value to all fields and puts sign on the most valuable one.
///Fields can change value if there are other marks around it.
///It works better then 'bot3', but there is still a slight chance to win
///If there are few fields with the same value, it chooses a random one
///</summary>
void bot4(char symboll)
{
	int randField;
	int mostValuableField;
	int amountOfBestFields = 0;
	int x[9];

	int symbol;
	int symbol2;
	if (symboll == 'o') symbol = 1;
	else symbol = 2;

	if (symbol == 1) symbol2 = 2;
	if (symbol == 2) symbol2 = 1;

	x[4] = 11;
	x[0] = 6;
	x[2] = 6;
	x[6] = 6;
	x[8] = 6;
	x[1] = 4;
	x[3] = 4;
	x[5] = 4;
	x[7] = 4;

	if (board.field[0][0] == symbol) { x[1] += 4; x[2] += 2; x[3] += 4; x[6] += 4; }
	if (board.field[0][2] == symbol) { x[0] += 4; x[1] += 2; x[5] += 4; x[8] += 4; }
	if (board.field[2][0] == symbol) { x[0] += 4; x[3] += 2; x[7] += 4; x[8] += 4; }
	if (board.field[2][2] == symbol) { x[2] += 4; x[5] += 2; x[6] += 4; x[7] += 4; }

	if (board.field[0][0] == symbol && board.field[1][0] == symbol) { x[6] += 20; }
	if (board.field[0][1] == symbol && board.field[1][1] == symbol) { x[7] += 20; }
	if (board.field[0][2] == symbol && board.field[1][2] == symbol) { x[8] += 20; }

	if (board.field[1][0] == symbol && board.field[2][0] == symbol) { x[0] += 20; }
	if (board.field[1][1] == symbol && board.field[2][1] == symbol) { x[1] += 20; }
	if (board.field[1][2] == symbol && board.field[2][2] == symbol) { x[2] += 20; }

	if (board.field[0][0] == symbol && board.field[0][1] == symbol) { x[2] += 20; }
	if (board.field[1][0] == symbol && board.field[1][1] == symbol) { x[5] += 20; }
	if (board.field[2][0] == symbol && board.field[2][1] == symbol) { x[8] += 20; }

	if (board.field[0][1] == symbol && board.field[0][2] == symbol) { x[0] += 20; }
	if (board.field[1][1] == symbol && board.field[1][2] == symbol) { x[3] += 20; }
	if (board.field[2][1] == symbol && board.field[2][2] == symbol) { x[6] += 20; }
	
	if (board.field[0][0] == symbol && board.field[2][0] == symbol) { x[3] += 20; }
	if (board.field[0][1] == symbol && board.field[2][1] == symbol) { x[4] += 20; }
	if (board.field[0][2] == symbol && board.field[2][2] == symbol) { x[5] += 20; }

	if (board.field[0][0] == symbol && board.field[0][2] == symbol) { x[1] += 20; }
	if (board.field[1][0] == symbol && board.field[1][2] == symbol) { x[4] += 20; }
	if (board.field[2][0] == symbol && board.field[2][2] == symbol) { x[7] += 20; }
	
	if (board.field[0][0] == symbol && board.field[1][1] == symbol) { x[8] += 20; }
	if (board.field[0][2] == symbol && board.field[1][1] == symbol) { x[6] += 20; }
	if (board.field[2][0] == symbol && board.field[1][1] == symbol) { x[2] += 20; }
	if (board.field[2][2] == symbol && board.field[1][1] == symbol) { x[0] += 20; }



	if (board.field[0][0] == symbol2 && board.field[1][0] == symbol2) { x[6] += 10; }
	if (board.field[0][1] == symbol2 && board.field[1][1] == symbol2) { x[7] += 10; }
	if (board.field[0][2] == symbol2 && board.field[1][2] == symbol2) { x[8] += 10; }

	if (board.field[1][0] == symbol2 && board.field[2][0] == symbol2) { x[0] += 10; }
	if (board.field[1][1] == symbol2 && board.field[2][1] == symbol2) { x[1] += 10; }
	if (board.field[1][2] == symbol2 && board.field[2][2] == symbol2) { x[2] += 10; }

	if (board.field[0][0] == symbol2 && board.field[0][1] == symbol2) { x[2] += 10; }
	if (board.field[1][0] == symbol2 && board.field[1][1] == symbol2) { x[5] += 10; }
	if (board.field[2][0] == symbol2 && board.field[2][1] == symbol2) { x[8] += 10; }

	if (board.field[0][1] == symbol2 && board.field[0][2] == symbol2) { x[0] += 10; }
	if (board.field[1][1] == symbol2 && board.field[1][2] == symbol2) { x[3] += 10; }
	if (board.field[2][1] == symbol2 && board.field[2][2] == symbol2) { x[6] += 10; }

	if (board.field[0][0] == symbol2 && board.field[2][0] == symbol2) { x[3] += 10; }
	if (board.field[0][1] == symbol2 && board.field[2][1] == symbol2) { x[4] += 10; }
	if (board.field[0][2] == symbol2 && board.field[2][2] == symbol2) { x[5] += 10; }

	if (board.field[0][0] == symbol2 && board.field[0][2] == symbol2) { x[1] += 10; }
	if (board.field[1][0] == symbol2 && board.field[1][2] == symbol2) { x[4] += 10; }
	if (board.field[2][0] == symbol2 && board.field[2][2] == symbol2) { x[7] += 10; }

	if (board.field[0][0] == symbol2 && board.field[1][1] == symbol2) { x[8] += 10; }
	if (board.field[0][2] == symbol2 && board.field[1][1] == symbol2) { x[6] += 10; }
	if (board.field[2][0] == symbol2 && board.field[1][1] == symbol2) { x[2] += 10; }
	if (board.field[2][2] == symbol2 && board.field[1][1] == symbol2) { x[0] += 10; }

	if (board.field[0][0] == symbol2 && board.field[2][2] == symbol2) { x[1] += 3; x[3] += 3; x[5] += 3; x[7] += 3; }
	if (board.field[0][2] == symbol2 && board.field[2][0] == symbol2) { x[1] += 3; x[3] += 3; x[5] += 3; x[7] += 3; }


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board.field[i][j] != 0) { x[i * 3 + j] = 0; }
		}
	}

	mostValuableField = x[0];
	for (int i = 1; i < 9; i++)
	{
		if (x[i] >= mostValuableField) { mostValuableField = x[i]; }
	}

	for (int i = 0; i < 9; i++)
	{
		if (x[i] == mostValuableField) { amountOfBestFields++; }
	}
	randField = rand() % amountOfBestFields;

	int *bestFields = new int[amountOfBestFields];

	int b = 0;
	int n = 0;

	for (int i = 0; i < 9; i++)
	{
		if (x[i] == mostValuableField) { bestFields[b] = i; b++; }
	}

	n = bestFields[0];
	board.field[n / 3][n % 3] = symbol;

	delete[] bestFields;
}

void neuralNetwork(char symboll)
{
	int symbol;
	if (symboll == 'o') symbol = 1;
	else symbol = 2;

	//Sets properties of the neural network before the first game
	//If you want you can skip this step, neural network will be working with default properties
	static bool firstGame = true;
	if (firstGame)
	{
		bot.SetAmmountOfChildrens(100);
		bot.SetMutationRate(0.01);
		bot.SetNextGenerationDescendantsPercentage(0.05);
		bot.SetTestAmmount(10);
		bot.Create(18, 12, 9);
		firstGame = false;
	}

	if (board.gameStatus != 0)
	{
		float result = 0;
		if (board.gameStatus == symbol) result = 1;
		if (board.gameStatus == 3) result = 0.75;
		bot.Update(result);

		board.gameStatus = 0;
	}

	//Sets input values of the neural network
	for (int i = 0; i < 9; i++)
	{
		if (board.field[i % 3][i / 3] == 1)
			bot.Input(i, 1);
		else bot.Input(i, 0);

		if (board.field[i % 3][i / 3] == 2)
			bot.Input(i + 9, 1);
		else bot.Input(i + 9, 0);
	}

	bot.CalculateOutputs();

	//Next lines of code search for the most valuable empty field, and place a symbol there
	float sum[9];

	for (int i = 0; i < 9; i++)
	{
		sum[i] = bot.Output(i);
	}

	float mostValuableField = -100000;

	for (int i = 0; i < 9; i++)
	{
		if (sum[i] > mostValuableField && board.field[i % 3][i / 3] == 0) mostValuableField = sum[i];
	}

	int iterator = 0;
	int bestFields[9];

	for (int i = 0; i < 9; i++)
	{
		if (sum[i] == mostValuableField && board.field[i % 3][i / 3] == 0)
		{
			bestFields[iterator] = i;
			iterator++;
		}
	}

	int randField = rand() % iterator;
	int field = bestFields[randField];

	board.field[field % 3][field / 3] = symbol;
}

void stop()
{
	static char symbol = '0';
	static long int iterator = 0;
	iterator++;
	if (iterator % 10000 == 0)
	{
		if (_kbhit()) symbol = _getwch();
	}

	if (symbol == 'p' || symbol == 'P') stopp = true;
	if (symbol == 'o' || symbol == 'O') stopp = false;
	if (stopp)
	{
		board.Draw();
		board.ShowWinRate();
		symbol = _getwch();

		if (symbol == 'l' || symbol == 'L') stopp2 = true;
		if (symbol == 'k' || symbol == 'K') stopp2 = false;
	}
}