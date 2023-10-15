#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include "Neuron.h"

class Board
{
public:
	std::vector <int> gameResults;	//0- draw, 1 - circle, 2 - cross
	int field[3][3]; // 0 - puste, 1-ko³ko, 2-krzy¿yk
	///<summary>
	/// 0 - the game is in progress
	/// 1 - circle has won
	/// 2 - cross has won
	/// 3 - draw
	///</summary>
	int gameStatus = 0;
	long int playedGames = 0;

	Board();
	void Draw();
	bool Wygrana();
	void ShowWinRate();

private:
	void ClearBoard();
};

