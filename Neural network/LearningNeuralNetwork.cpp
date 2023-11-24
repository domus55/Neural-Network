#include "LearningNeuralNetwork.h"
#include <algorithm>

LearningNeuralNetwork::LearningNeuralNetwork(std::initializer_list<unsigned int> layers, unsigned int ammountOfChildren)
	:bestNeuralNetwork(layers), ammountOfChildren(ammountOfChildren)
{
	srand(time(NULL));

	if (layers.size() < 2)
	{
		throw std::invalid_argument("Neural Network needs at least 2 layers!");
	}

	for (unsigned int i = 0; i < ammountOfChildren; i++)
	{
		NeuralNetwork n(layers);
		n.SetMutationRate(mutationPercentage);
		neuralNetwork.push_back(n);
	}

	nextGenerationDescendants = (int)(nextGenerationDescendantsPercentage * ammountOfChildren);
	if (nextGenerationDescendants % 2 == 1)
		nextGenerationDescendants++;
}

void LearningNeuralNetwork::SetArguments(float nextGenerationDescendantsPercentage, float mutationPercentage)
{
	this->nextGenerationDescendantsPercentage = nextGenerationDescendantsPercentage;
	this->mutationPercentage = mutationPercentage;

	nextGenerationDescendants = (int)(nextGenerationDescendantsPercentage * ammountOfChildren);
	if (nextGenerationDescendants % 2 == 1)
		nextGenerationDescendants++;

	for (NeuralNetwork i : neuralNetwork)
	{
		i.SetMutationRate(mutationPercentage);
	}
}

void LearningNeuralNetwork::SetTestAmmount(unsigned int ammount)
{
	testAmmount = ammount;
}

void LearningNeuralNetwork::Update(float win)
{
	if (finishLearning)
		return;

	if (activeTest == 0)
	{
		neuralNetwork[activeNetwork].WinRate = win;
	}
	else
	{
		float allPoints = neuralNetwork[activeNetwork].WinRate * activeTest;
		neuralNetwork[activeNetwork].WinRate = (allPoints + win) / (float)(activeTest + 1);
	}
	
	activeTest++;

	if (activeTest >= testAmmount)
	{
		activeNetwork++;
		activeTest = 0;
	}
	

	if (activeNetwork >= ammountOfChildren)
	{
		activeNetwork = 0;
		NextGeneration();
	}
}

void LearningNeuralNetwork::Input(unsigned int neuronId, float value)
{
	if(finishLearning)
		bestNeuralNetwork.Input(neuronId, value);
	else
		neuralNetwork[activeNetwork].Input(neuronId, value);
}

void LearningNeuralNetwork::CalculateOutputs()
{
	if (finishLearning)
		bestNeuralNetwork.CalculateTheOutput();
	else
		neuralNetwork[activeNetwork].CalculateTheOutput();
}

float LearningNeuralNetwork::Output(unsigned int neuronId)
{
	if (finishLearning)
		return bestNeuralNetwork.Output(neuronId);
	else
		return neuralNetwork[activeNetwork].Output(neuronId);
}

void LearningNeuralNetwork::SetFinishLearning(bool finish)
{
	if (finish)
	{
		activeTest = 0;
		activeNetwork = 0;
	}

	finishLearning = finish;
}

bool LearningNeuralNetwork::GetFinishLearning()
{
	return finishLearning;
}

int LearningNeuralNetwork::GetGeneration()
{
	return generation;
}

float LearningNeuralNetwork::GetBestWinRate()
{
	return bestNeuralNetwork.WinRate;
}

void LearningNeuralNetwork::NextGeneration()
{
	NeuralNetworksEvolve();
	MutateAllNetworks();
	generation++;
}

void LearningNeuralNetwork::NeuralNetworksEvolve()
{
	std::sort(neuralNetwork.begin(), neuralNetwork.end(), [](NeuralNetwork n1, NeuralNetwork n2) {return n1.WinRate > n2.WinRate; });
	
	//message for debbuging
	if (false)
	{
		for (NeuralNetwork n : neuralNetwork)
		{
			std::cout << (int)(n.WinRate * 1000) / 10.0 << " ";
		}
	}
	//std::cout << "\n\n";

	if (neuralNetwork[0].WinRate > bestNeuralNetwork.WinRate && !finishLearning)
	{
		bestNeuralNetwork.Copy(neuralNetwork[0]);
		bestNeuralNetwork.WinRate = neuralNetwork[0].WinRate;
		//std::cout << "\n\tbestNeuralNetwork.WinRate: " << (int)(bestNeuralNetwork.WinRate * 1000) / 10.0 << "\n";
	}

	for (unsigned int i = 0; i < nextGenerationDescendants / 2; i++) 
	{
		neuralNetwork[i].Merge(neuralNetwork[i + nextGenerationDescendants / 2]);
	}

	for (unsigned int i = nextGenerationDescendants; i < ammountOfChildren; i++)
	{
		neuralNetwork[i].Copy(neuralNetwork[rand() % nextGenerationDescendants]);
	}
}

void LearningNeuralNetwork::MutateAllNetworks()
{
	for (unsigned int i = 0; i < ammountOfChildren; i++)
	{
		neuralNetwork[i].Mutate();
	}
}
