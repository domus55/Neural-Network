#include "Board.h"

using namespace std;


Board::Board()
{
	ClearBoard();
}

void Board::Draw()
{
	system("cls");

	if (field[0][0] == 1) cout << " " << char(218) << char(196) << char(191) << " ";        //Linia 1,1
	if (field[0][0] == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[0][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[0][1]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";
	if (field[0][1]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[0][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[0][2]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";
	if (field[0][2]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[0][2]  == 0) cout << "     ";
	cout << endl;

	if (field[0][0]  == 1) cout << " " << char(179) << " " << char(179) << " ";        //Linia 1,2
	if (field[0][0]  == 2) cout << "  " <<"X"<< "  ";
	if (field[0][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[0][1]  == 1) cout << " " << char(179) << " " << char(179) << " ";
	if (field[0][1]  == 2) cout << "  " <<"X"<< "  ";
	if (field[0][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[0][2]  == 1) cout << " " << char(179) << " " << char(179) << " ";
	if (field[0][2]  == 2) cout << "  " <<"X"<< "  ";
	if (field[0][2]  == 0) cout << "     ";
	cout << endl;

	if (field[0][0]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";        //Linia 1,3
	if (field[0][0]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[0][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[0][1]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";
	if (field[0][1]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[0][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[0][2]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";
	if (field[0][2]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[0][2]  == 0) cout << "     ";
	cout << endl;

	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(206) << char(205) << char(205) << char(205) << char(205) << char(205) << char(206) << char(205) << char(205) << char(205) << char(205) << char(205) << endl;

	if (field[1][0]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";        //Linia 2,1
	if (field[1][0]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[1][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[1][1]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";
	if (field[1][1]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[1][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[1][2]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";
	if (field[1][2]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[1][2]  == 0) cout << "     ";
	cout << endl;

	if (field[1][0]  == 1) cout << " " << char(179) << " " << char(179) << " ";        //Linia 2,2
	if (field[1][0]  == 2) cout << "  " << "X" << "  ";
	if (field[1][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[1][1]  == 1) cout << " " << char(179) << " " << char(179) << " ";
	if (field[1][1]  == 2) cout << "  " << "X" << "  ";
	if (field[1][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[1][2]  == 1) cout << " " << char(179) << " " << char(179) << " ";
	if (field[1][2]  == 2) cout << "  " << "X" << "  ";
	if (field[1][2]  == 0) cout << "     ";
	cout << endl;

	if (field[1][0]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";        //Linia 2,3
	if (field[1][0]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[1][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[1][1]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";
	if (field[1][1]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[1][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[1][2]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";
	if (field[1][2]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[1][2]  == 0) cout << "     ";
	cout << endl;

	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(206) << char(205) << char(205) << char(205) << char(205) << char(205) << char(206) << char(205) << char(205) << char(205) << char(205) << char(205) << endl;

	if (field[2][0]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";        //Linia 3,1
	if (field[2][0]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[2][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[2][1]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";
	if (field[2][1]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[2][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[2][2]  == 1) cout << " " << char(218) << char(196) << char(191) << " ";
	if (field[2][2]  == 2) cout << " " << "\\" << " " << "/" << " ";
	if (field[2][2]  == 0) cout << "     ";
	cout << endl;
	if (field[2][0]  == 1) cout << " " << char(179) << " " << char(179) << " ";        //Linia 3,2
	if (field[2][0]  == 2) cout << "  " << "X" << "  ";
	if (field[2][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[2][1]  == 1) cout << " " << char(179) << " " << char(179) << " ";
	if (field[2][1]  == 2) cout << "  " << "X" << "  ";
	if (field[2][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[2][2]  == 1) cout << " " << char(179) << " " << char(179) << " ";
	if (field[2][2]  == 2) cout << "  " << "X" << "  ";
	if (field[2][2]  == 0) cout << "     ";
	cout << endl;

	if (field[2][0]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";        //Linia 3,3
	if (field[2][0]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[2][0]  == 0) cout << "     ";
	cout << char(186);
	if (field[2][1]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";
	if (field[2][1]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[2][1]  == 0) cout << "     ";
	cout << char(186);
	if (field[2][2]  == 1) cout << " " << char(192) << char(196) << char(217) << " ";
	if (field[2][2]  == 2) cout << " " << "/" << " " << "\\" << " ";
	if (field[2][2]  == 0) cout << "     ";
	cout << endl;
}

bool Board::Wygrana()
{
	//1 - circle, 2 - cross
	int winner = 0;

	if (field[0][0] == 1 && field[0][1] == 1 && field[0][2] == 1) { winner = 1; }
	if (field[1][0] == 1 && field[1][1] == 1 && field[1][2] == 1) { winner = 1; }
	if (field[2][0] == 1 && field[2][1] == 1 && field[2][2] == 1) { winner = 1; }

	if (field[0][0] == 1 && field[1][0] == 1 && field[2][0] == 1) { winner = 1; }
	if (field[0][1] == 1 && field[1][1] == 1 && field[2][1] == 1) { winner = 1; }
	if (field[0][2] == 1 && field[1][2] == 1 && field[2][2] == 1) { winner = 1; }

	if (field[0][0] == 1 && field[1][1] == 1 && field[2][2] == 1) { winner = 1; }
	if (field[0][2] == 1 && field[1][1] == 1 && field[2][0] == 1) { winner = 1; }


	if (field[0][0] == 2 && field[0][1] == 2 && field[0][2] == 2) { winner = 2; }
	if (field[1][0] == 2 && field[1][1] == 2 && field[1][2] == 2) { winner = 2; }
	if (field[2][0] == 2 && field[2][1] == 2 && field[2][2] == 2) { winner = 2; }
					  
	if (field[0][0] == 2 && field[1][0] == 2 && field[2][0] == 2) { winner = 2; }
	if (field[0][1] == 2 && field[1][1] == 2 && field[2][1] == 2) { winner = 2; }
	if (field[0][2] == 2 && field[1][2] == 2 && field[2][2] == 2) { winner = 2; }
					  
	if (field[0][0] == 2 && field[1][1] == 2 && field[2][2] == 2) { winner = 2; }
	if (field[0][2] == 2 && field[1][1] == 2 && field[2][0] == 2) { winner = 2; }

	if (winner != 0) 
	{ 
		gameStatus = winner;
		gameResults.push_back(winner);

		ClearBoard();
		playedGames++; 
		if (playedGames % 10000 == 0) 
		{ 
			ShowWinRate(); 
		} 
		return true; 
	}

	bool allFieldsAreOccupied = false;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] == 0) allFieldsAreOccupied = true;
		}
	}

	if (!allFieldsAreOccupied) 
	{
		gameStatus = 3;
		gameResults.push_back(0);
		ClearBoard(); 
		playedGames++; 
		if (playedGames % 10000 == 0) 
		{ 
			ShowWinRate(); 
		} 
		return true; 
	}
	return false;
}

void Board::ShowWinRate()
{
	if (gameResults.size() > 3001)
	{
		gameResults.erase(gameResults.begin(), gameResults.begin() + (gameResults.size() - 3000));
	}

	int draw = 0;
	int circle = 0;
	int cross = 0;
	int totalGames = gameResults.size();

	for (int i = 0; i < totalGames; i++)
	{
		if (gameResults[i] == 0) draw++;
		if (gameResults[i] == 1) circle++;
		if (gameResults[i] == 2) cross++;
	}

	if (totalGames == 0) totalGames = 1;

	//cout << "Gen: " << Neuron::gen <<"\n";
	cout << "Cross win rate: " << round(cross * 1000 / (float) totalGames) / 10.0 << "%" << "\n";
	cout << "Circle win rate: " << round(circle * 1000 / (float) totalGames) / 10.0 << "%" << "\n";
	cout << "Draw: " << round(draw * 1000 / (float) totalGames) / 10.0 << "%" << "\n";
	cout << "\n";
}


void Board::ClearBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = 0;
		}
	}
}

