# Neural-Network
A simple artificial neural network designed for improvement through evolutionary learning. Developed in C++ without reliance on external libraries, 
this neural network is available for download and integration into your own projects.

# Learning to play snake
The following illustrates how this neural network can learn to play snake game.

### Technical info
- The game board is 21x21 implying a maximum snake value of 441
- The network used in this example comprises 14 input neurons, one hidden layer with 6 neurons and 3 output neurons
- Mutation percentage: 5%
- Number of children: 200
- Test ammount: 10


#### Inputs
The neural network takes as input the distances to obstacles and food. The distance is calculated using the following formula: <br>
```
(distance + 1 - BOARD_SIZE) / (float)(BOARD_SIZE - 1) * -1;
``` 
Quick explenation:
- distance - distance to nearest food/obstacle ranging from 0 to BOARD_SIZE - 1
- BOARD_SIZE - the size of the game board, set to 21 in this case.

**Return values** range between 0 and 1. A value of one indicates that an obstacle or food is in the field next to the snake head, 
while zero signifies the absence of food or that an obstacle is in the furthest possible place.

### Learning
|Gen|Learning time| Average length|
|---|---|---|
|gen 1 |00:00| 0.0|
|gen 10 |00:18.7|16.3|
|gen 25 |00:58.2|21.4|
|gen 100 |10:29.3|43.5|

### Learning preview
|gen 1|gen 2|gen 10|gen 25|gen 100|
|---|---|---|---|---|
|![gif](https://github.com/domus55/Neural-Network/blob/main/Readme%20files/Gen1.gif)|![gif](https://github.com/domus55/Neural-Network/blob/main/Readme%20files/Gen2.gif)|![gif](https://github.com/domus55/Neural-Network/blob/main/Readme%20files/Gen10.gif)|![gif](https://github.com/domus55/Neural-Network/blob/main/Readme%20files/Gen25.gif)|![gif](https://github.com/domus55/Neural-Network/blob/main/Readme%20files/Gen100.gif)|

# Usage
It is recommended to first familiarize yourself with how this artificial neural network learns - [Learning process](https://github.com/domus55/Neural-Network/blob/main/Docs.md#learning-algorithm).<br>
To use this neural network, follow these steps:
### Import
Add the following header and source files to your project: `Neuron`, `NeuralNetwork` and `LearningNeuralNetwork`<br>
Include the `LearningNeuralNetwork` header in your code:
```cpp
#include "LearningNeuralNetwork.h"
```

### Create object 
Create artificial neural network by creating LearningNeuralNetwork object. Note that
as a constructor argument you need to provide an initializer list. The values in this list have the following meanings:
- The first value indicates the number of neurons in the input layer, representing how many different inputs the network can distinguish.
- The last value represents the number of neurons in the output layer.
- All values in between define the number of neurons in each hidden layer.

```cpp
//network with 14 neurons in the input layer, 2 hidden layers 6 neurons each, 3 output neurons
LearningNeuralNetwork bot({ 14, 6, 6, 3 });
```

### Optional steps. 
You have the option to pass arguments to neural network by calling `SetArguments(float descendantsPercentage, float mutationPercentage)`. It's important to do this before starting the learning process.
- `descendantsPercentage` is the percentage of how many children will be used to create the next generation.
For example, if your artificial neural network consists of 200 children and you set `descendantsPercentage` to 0.2, then the top 40 best children
will be used to create the next generation. The default value is 0.05.
- `mutationPercentage` indicates how much the network mutates. The default value is 0.05.
```cpp
//descendantsPercentage 10%, mutationPercentage 5%
bot.SetArguments(0.1f, 0.05f);
```

Additionally, you can determine how many tests each child will perform. This is particularly useful in games like TicTacToe where it's challenging to assess a child's performance based on a single test.
```cpp
bot.SetTestAmmount(10);
```
### Passing input values 
```cpp
//passing 0.3 to first neuron in input layer
bot.Input(0, 0.3);
//passing 0.5 to second neuron in input layer
bot.Input(1, 0.5);
```
### Receiving output values
```cpp
//you need to call CalculateOutputs method before receiving output values
bot.CalculateOutputs();
//get value of first three neurons from output layer
float out1 = bot.Output(0);
float out2 = bot.Output(1);
float out3 = bot.Output(2);
```
### Learning 
After each game, inform the network of its performance by calling the `Update(float win)` method. Note:<br>
`win` is a float value ranging between 0 and 1. A value of 0 indicates that the network made all possible mistakes, while a value of 1 signifies that the network is perfect and doesn't need to improve.
```cpp
bot.Update(0.9);
```
### Finishing learning
If your best neural network achieves satisfactory results then you can call `SetFinishLearning(true)`. 
From this point on, the network will stop learning and use the best-performing child to calculate its output values.
```cpp
if (bot.GetBestWinRate() > 0.9f && !bot.GetFinishLearning())
{
  bot.SetFinishLearning(true);
}
```

## Further reading
[Documentation](https://github.com/domus55/Neural-Network/blob/main/Docs.md#learningneuralnetwork-documentation) of LearningNeuralNetwork. 

## Example Code for training a neural network to play snake
```cpp
#include <iostream>
#include "SnakeGame.h"
#include "LearningNeuralNetwork.h"

int main(int argc, char* argv[])
{
	SnakeGame snake;
	LearningNeuralNetwork bot({ 14, 6, 3 });
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
```
