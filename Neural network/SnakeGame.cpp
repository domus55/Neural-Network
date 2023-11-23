#include "SnakeGame.h"

SnakeGame::SnakeGame()
	:hOut(GetStdHandle(STD_OUTPUT_HANDLE))
{
	srand(time(NULL));
	restartGame();

	//Remove cursor in cmd
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void SnakeGame::restartGame()
{
	gameStatus = GAME_END;
	maxSize = bodyPosition.size();
	avgSize = (avgSize * 9999 + maxSize) / (float)10000;
	snakeInstance++;

	currentDirection = snakeDirection::UP;
	headPosition.x = BOARD_SIZE / 2;
	headPosition.y = BOARD_SIZE / 2;
	bodyPosition.clear();

	createFood();
}

void SnakeGame::move(moveDirection move)
{
	gameStatus = GAME_IN_PROGRESS;
	TTL--;

	//move body
	for (int i = bodyPosition.size() - 1; i > 0; i--)
	{
		bodyPosition[i] = bodyPosition[i - 1];
	}
	if (bodyPosition.size() > 0)
	{
		bodyPosition[0] = headPosition;
	}

	//move head
	currentDirection = static_cast<snakeDirection>((currentDirection + move + 4) % 4);

	if (currentDirection == snakeDirection::LEFT)
	{
		headPosition.x--;
	}
	else if (currentDirection == snakeDirection::UP)
	{
		headPosition.y--;
	}
	else if (currentDirection == snakeDirection::RIGHT)
	{
		headPosition.x++;
	}
	else if (currentDirection == snakeDirection::DOWN)
	{
		headPosition.y++;
	}

	// Write to board
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = 0;
		}
	}

	for (vector2 bodyPos : bodyPosition)
	{
		board[bodyPos.x][bodyPos.y] = 1;
	}

	//Check death
	if (TTL <= 0 || headPosition.x < 0 || headPosition.y < 0 || headPosition.x >= BOARD_SIZE || headPosition.y >= BOARD_SIZE || board[headPosition.x][headPosition.y] == 1)
	{
		restartGame();
	}

	//Eat food
	if (headPosition == foodPosition)
	{
		createFood();
		bodyPosition.push_back({ headPosition });
	}

	//printBoard();
}

float SnakeGame::getDistanceToObstacle(moveDirection move)
{
	snakeDirection direction = static_cast<snakeDirection>((currentDirection + move + 4) % 4);
	int distance = 0;

	if (direction == snakeDirection::LEFT)
	{
		for (int i = headPosition.x - 1; i >= 0; i--)
		{
			if (board[i][headPosition.y] == 1)
				break;
			distance++;
		}
	}
	else if (direction == snakeDirection::UP)
	{
		for (int i = headPosition.y - 1; i >= 0; i--)
		{
			if (board[headPosition.x][i] == 1)
				break;
			distance++;
		}
	}
	else if (direction == snakeDirection::RIGHT)
	{
		for (int i = headPosition.x + 1; i < BOARD_SIZE; i++)
		{
			if (board[i][headPosition.y] == 1)
				break;
			distance++;
		}
	}
	else if (direction == snakeDirection::DOWN)
	{
		for (int i = headPosition.y + 1; i < BOARD_SIZE; i++)
		{
			if (board[headPosition.x][i] == 1)
				break;
			distance++;
		}
	}

	return (distance + 1 - BOARD_SIZE) / (float)(BOARD_SIZE - 1) * -1;
}

float SnakeGame::getDistanceToObstacle(lookDirection look)
{
	/* lookDir is diagonal direction
	* 0 - bottom right
	* 1 - bottom left
	* 2 - upper left
	* 3 - upper right
	*/
	const int lookDir = static_cast<int>((currentDirection + look + 4) % 4);
	int distance = 0;
	vector2 checkField = headPosition;
	bool clearField = true;
	
	do
	{
		if (lookDir == 0 || lookDir == 1)
			checkField.y++;
		else
			checkField.y--;

		if (lookDir == 1 || lookDir == 2)
			checkField.x--;
		else
			checkField.x++;

		if (board[checkField.x][checkField.y] ||
			!(checkField.x >= 0 && checkField.y >= 0 && checkField.x < BOARD_SIZE && checkField.y < BOARD_SIZE))
			clearField = false;
		else
			distance++;
	}
	while (clearField);
	
	return (distance + 1 - BOARD_SIZE) / (float)(BOARD_SIZE - 1) * -1;
}

int SnakeGame::getSize()
{
	return maxSize;
}

float SnakeGame::getDistanceToFood(moveDirection move)
{
	snakeDirection direction = static_cast<snakeDirection>((currentDirection + move + 4) % 4);
	int distance = BOARD_SIZE;

	if (headPosition.y == foodPosition.y)
	{
		if (direction == snakeDirection::LEFT)
			distance = headPosition.x - foodPosition.x;

		if (direction == snakeDirection::RIGHT)
			distance = foodPosition.x - headPosition.x;
	}
	if (headPosition.x == foodPosition.x)
	{
		if (direction == snakeDirection::UP)
			distance = headPosition.y - foodPosition.y;

		if (direction == snakeDirection::DOWN)
			distance = foodPosition.y - headPosition.y;
	}

	if (distance < 0)
		distance = BOARD_SIZE;

	return (distance - BOARD_SIZE) / (float)(BOARD_SIZE - 1) * -1;
}

float SnakeGame::getDistanceToFood(lookDirection look)
{
	/* lookDir is diagonal direction
	* 0 - bottom right
	* 1 - bottom left
	* 2 - upper left
	* 3 - upper right
	*/
	const int lookDir = static_cast<int>((currentDirection + look + 4) % 4);
	int distance = 0;
	vector2 checkField = headPosition;
	bool clearField = true;
	bool foundFood = false;

	while(checkField.x >= 0 && checkField.y >= 0 && checkField.x < BOARD_SIZE && checkField.y < BOARD_SIZE)
	{
		if (lookDir == 0 || lookDir == 1)
			checkField.y++;
		else
			checkField.y--;

		if (lookDir == 1 || lookDir == 2)
			checkField.x--;
		else
			checkField.x++;

		if (foodPosition.x == checkField.x && foodPosition.y == checkField.y)
		{
			foundFood = true;
			break;
		}

		distance++;
	}

	if (!foundFood)
		distance = BOARD_SIZE - 1;

	return (distance + 1 - BOARD_SIZE) / (float)(BOARD_SIZE - 1) * -1;
}

void SnakeGame::printCurrentDirection()
{
	if (currentDirection == snakeDirection::LEFT)
	{
		std::cout << "Left";
	}
	if (currentDirection == snakeDirection::UP)
	{
		std::cout << "UP";
	}
	if (currentDirection == snakeDirection::RIGHT)
	{
		std::cout << "RIGHT";
	}
	if (currentDirection == snakeDirection::DOWN)
	{
		std::cout << "DOWN";
	}
}

void SnakeGame::printBoard(int generation)
{
	if (snakeInstance % 1000 == 0 && TTL == MAX_TTL - 1 && bodyPosition.size() == 0)
	{
		std::cout << "Gen: "<< generation << "\tAvarage size: " << avgSize << "\n";
	}

	//system("cls");

	if ((!showBoard && snakeInstance % 1000 == 0 && _kbhit()) || (showBoard && _kbhit()))
	{
		char symbol = ' ';
		symbol = _getwch();
		if (symbol == 'p' || symbol == 'P')
		{
			showBoard = false;
			system("cls");
		}
		if (symbol == 'o' || symbol == 'O')
			showBoard = true;
	}

	if (!showBoard)
		return;

	//Used to get rid of screen flickering
	std::cout.flush();
	SetConsoleCursorPosition(hOut, { (SHORT)0, (SHORT)0 });
	//printCurrentDirection();
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			bool emptySpace = false;
			if (headPosition.x == j && headPosition.y == i) std::cout << "OO";
			else if (foodPosition.x == j && foodPosition.y == i) std::cout << "XX";
			else
			{
				emptySpace = true;
				for (vector2 bodyPos : bodyPosition)
				{
					if (bodyPos.x == j && bodyPos.y == i)
					{
						std::cout << "##";
						emptySpace = false;
					}
				}
			}
			if (emptySpace) std::cout << "  ";
		}
		std::cout << "|\n";
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << "--";
	}
	std::cout << "+\n";

	/*std::cout << "\ndistance TURN_HARD_LEFT: " << getDistanceToObstacle(lookDirection::TURN_HARD_LEFT);
	std::cout << "\ndistance TURN_SLIGHTLY_LEFT: " << getDistanceToObstacle(lookDirection::TURN_SLIGHTLY_LEFT);
	std::cout << "\ndistance TURN_SLIGHTLY_RIGHT: " << getDistanceToObstacle(lookDirection::TURN_SLIGHTLY_RIGHT);
	std::cout << "\ndistance TURN_HARD_RIGHT: " << getDistanceToObstacle(lookDirection::TURN_HARD_RIGHT);

	std::cout << "\ndistance left: " << getDistanceToObstacle(moveDirection::TURN_LEFT);
	std::cout << "\ndistance forward: " << getDistanceToObstacle(moveDirection::FORWARD);
	std::cout << "\ndistance right: " << getDistanceToObstacle(moveDirection::TURN_RIGHT);

	std::cout << "\n\nFood distance: ";

	std::cout << "\ndistance left: " << getDistanceToFood(moveDirection::TURN_LEFT);
	std::cout << "\ndistance forward: " << getDistanceToFood(moveDirection::FORWARD);
	std::cout << "\ndistance right: " << getDistanceToFood(moveDirection::TURN_RIGHT);

	std::cout << "\ndistance TURN_HARD_LEFT: " << getDistanceToFood(lookDirection::TURN_HARD_LEFT);
	std::cout << "\ndistance TURN_SLIGHTLY_LEFT: " << getDistanceToFood(lookDirection::TURN_SLIGHTLY_LEFT);
	std::cout << "\ndistance TURN_SLIGHTLY_RIGHT: " << getDistanceToFood(lookDirection::TURN_SLIGHTLY_RIGHT);
	std::cout << "\ndistance TURN_HARD_RIGHT: " << getDistanceToFood(lookDirection::TURN_HARD_RIGHT);*/
}

void SnakeGame::createFood()
{
	bool validPosition;

	do
	{
		validPosition = true;

		foodPosition.x = rand() % BOARD_SIZE;
		foodPosition.y = rand() % BOARD_SIZE;

		if (headPosition == foodPosition || board[foodPosition.x][foodPosition.y])
		{
			validPosition = false;
		}
	} while (!validPosition);

	TTL = MAX_TTL;
}
