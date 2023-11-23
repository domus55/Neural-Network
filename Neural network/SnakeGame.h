#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include "LearningNeuralNetwork.h"

class SnakeGame
{
public:
	enum status
	{
		GAME_END,
		GAME_IN_PROGRESS,
	};

	enum moveDirection
	{
		TURN_LEFT = -1,
		FORWARD, 
		TURN_RIGHT,
	};

	enum lookDirection
	{
		TURN_HARD_LEFT = 0,
		TURN_SLIGHTLY_LEFT,
		TURN_SLIGHTLY_RIGHT,
		TURN_HARD_RIGHT
	};

	SnakeGame();
	void restartGame();
	void move(moveDirection);
	//returns value in range 1-0 where 1 means really close, and 0 means far
	float getDistanceToObstacle(moveDirection);
	float getDistanceToObstacle(lookDirection);
	float getDistanceToFood(moveDirection);
	float getDistanceToFood(lookDirection);
	void printBoard(int generation);
	int getSize();
	status gameStatus = GAME_IN_PROGRESS;
	static constexpr int BOARD_SIZE = 21;


private:
	enum snakeDirection 
	{
		LEFT = 0,
		UP,
		RIGHT,
		DOWN,
	};

	struct vector2 {
		int x, y;

		bool operator==(const vector2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
	};

	static constexpr int MAX_TTL = 200;
	int board[BOARD_SIZE][BOARD_SIZE];
	vector2 headPosition;
	std::vector<vector2> bodyPosition;
	vector2 foodPosition;
	snakeDirection currentDirection;
	int maxSize = 0;
	int TTL;
	bool showBoard = false;
	float avgSize = 0;
	long long snakeInstance = 0;
	const HANDLE hOut;

	void createFood();
};

