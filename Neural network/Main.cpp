#include <iostream>
#include "SnakeGame.h"
#include "LearningNeuralNetwork.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	//testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();

	std::cout << "Use 'o', and 'p' buttons, to watch snake \n";
	Sleep(1000);
	std::cout << "Click any key\n\n";
	_getch();

	SnakeGame snake;
	LearningNeuralNetwork bot({ 14, 6, 3 });

	//Sets properties of the neural network, use before the first game
	//If you want you can skip this step, neural network will be working with default properties
	bot.SetArguments(0.05f, 0.05f);
	bot.SetTestAmmount(10);

	for (;;)
	{
		if (snake.gameStatus == snake.GAME_END)
		{
			float result = static_cast<float>(snake.getSize());
			bot.Update(result / (float)(snake.BOARD_SIZE * snake.BOARD_SIZE));
		}

		bot.Input(0, snake.getDistanceToObstacle(snake.TURN_HARD_LEFT));
		bot.Input(1, snake.getDistanceToObstacle(snake.TURN_LEFT));
		bot.Input(2, snake.getDistanceToObstacle(snake.TURN_SLIGHTLY_LEFT));
		bot.Input(3, snake.getDistanceToObstacle(snake.FORWARD));
		bot.Input(4, snake.getDistanceToObstacle(snake.TURN_SLIGHTLY_RIGHT));
		bot.Input(5, snake.getDistanceToObstacle(snake.TURN_RIGHT));
		bot.Input(6, snake.getDistanceToObstacle(snake.TURN_HARD_RIGHT));
		bot.Input(7, snake.getDistanceToFood(snake.TURN_HARD_LEFT));
		bot.Input(8, snake.getDistanceToFood(snake.TURN_LEFT));
		bot.Input(9, snake.getDistanceToFood(snake.TURN_SLIGHTLY_LEFT));
		bot.Input(10, snake.getDistanceToFood(snake.FORWARD));
		bot.Input(11, snake.getDistanceToFood(snake.TURN_SLIGHTLY_RIGHT));
		bot.Input(12, snake.getDistanceToFood(snake.TURN_RIGHT));
		bot.Input(13, snake.getDistanceToFood(snake.TURN_HARD_RIGHT));

		bot.CalculateOutputs();

		float out[3];
		for (int i = 0; i < 3; i++)
		{
			out[i] = bot.Output(i);
		}

		int max = std::distance(out, std::max_element(out, out + sizeof(out) / sizeof(int)));

		snake.move(static_cast<SnakeGame::moveDirection>(max - 1));
		snake.printBoard(bot.GetGeneration());

		if (bot.GetBestWinRate() > 0.05f && !bot.GetFinishLearning())
		{
			std::cout<<"\n\nFinish learning!\n";
			bot.SetFinishLearning(true);
		}
	}

	return 0;
}