#include <iostream>
#include "SnakeGame.h"
#include "Neuron.h"
#include "LearningNeuralNetwork.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	//testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();

	SnakeGame snake;
	
	/*for (;;)
	{
		char move = _getwch();
		if (move == 'a') snake.move(SnakeGame::TURN_LEFT);
		if (move == 'w') snake.move(SnakeGame::FORWARD);
		if (move == 'd') snake.move(SnakeGame::TURN_RIGHT);
	}*/

	//Sets properties of the neural network before the first game
	//If you want you can skip this step, neural network will be working with default properties
	LearningNeuralNetwork bot;
	
	bot.SetAmmountOfChildren(200);//200
	bot.SetMutationRate(0.05f);
	bot.SetNextGenerationDescendantsPercentage(0.05f);
	bot.SetTestAmmount(10);
	bot.Create({ 14, 6, 3 });

	for (;;)
	{
		if (snake.gameStatus == snake.GAME_END)
		{
			float result = static_cast<float>(snake.getSize());
			bot.Update(result / (float)100.0);	//TODO change to board size
			//std::cout << result << " ";
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
		snake.printBoard();
	}

	return 0;
}