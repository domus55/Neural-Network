#include "LearningNeuralNetwork.h"

int LearningNeuralNetwork::generation = 1;

void LearningNeuralNetwork::Create(std::initializer_list<unsigned int> layers)
{
	nextGenerationDescendants = (int)(nextGenerationDescendantsPercentage * ammountOfChildren);
	theBestNetworksIds.resize(nextGenerationDescendants);

	for (int i = 0; i < nextGenerationDescendants; i++)
	{
		theBestNetworksIds[i] = 0;
	}

	for (int i = 0; i < ammountOfChildren; i++)
	{
		NeuralNetwork n(layers);
		n.SetMutationRate(mutationRate);
		neuralNetwork.push_back(n);
	}
}

void LearningNeuralNetwork::SetAmmountOfChildren(int ammount)
{
	ammountOfChildren = ammount;
}

void LearningNeuralNetwork::SetMutationRate(float rate)
{
	mutationRate = rate;
}

void LearningNeuralNetwork::SetTestAmmount(int ammount)
{
	testAmmount = ammount;
}

void LearningNeuralNetwork::SetNextGenerationDescendantsPercentage(float rate)
{
	if (rate < 0 || rate > 1)
		throw std::invalid_argument("Descendants percentage needs to be between 0-1");
	nextGenerationDescendantsPercentage = rate;
}

void LearningNeuralNetwork::Update(float win)
{
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

void LearningNeuralNetwork::Input(int neuronId, float value)
{
	neuralNetwork[activeNetwork].Input(neuronId, value);
}

void LearningNeuralNetwork::CalculateOutputs()
{
	neuralNetwork[activeNetwork].CalculateTheOutput();
}

float LearningNeuralNetwork::Output(int neuronId)
{
	return neuralNetwork[activeNetwork].Output(neuronId);
}

void LearningNeuralNetwork::NextGeneration()
{
	FindTheBestNetworks();
	MergeTheBestNetworks();
	CopyTheBestNetworksToAllNetworks();
	MutateAllNetworks();
	generation++;
}

void LearningNeuralNetwork::FindTheBestNetworks()
{
	float maxWinRate = 0;

	for (int i = 0; i < nextGenerationDescendants; i++)
	{
		maxWinRate = 0;

		for (int j = 0; j < neuralNetwork.size(); j++)
		{
			if (neuralNetwork[j].WinRate > maxWinRate)
			{
				theBestNetworksIds[i] = j;
				maxWinRate = neuralNetwork[j].WinRate;
			}
		}

		neuralNetwork[theBestNetworksIds[i]].WinRate *= -1;
	}

	for (int i = 0; i < nextGenerationDescendants; i++)
	{
		neuralNetwork[theBestNetworksIds[i]].WinRate *= -1;
	}
}

void LearningNeuralNetwork::MergeTheBestNetworks()
{
	for (int i = 0; i < nextGenerationDescendants / 2; i++)
	{
		if (i != nextGenerationDescendants - i - 1)
		{
			neuralNetwork[theBestNetworksIds[i]].Merge(neuralNetwork[theBestNetworksIds[nextGenerationDescendants - i - 1]]);
		}
	}
}

void LearningNeuralNetwork::CopyTheBestNetworksToAllNetworks()
{
	for (int i = 0; i < ammountOfChildren; i++)
	{
		bool shouldContinue = false;
		for (int j = 0; j < nextGenerationDescendants; j++)
		{
			if (theBestNetworksIds[j] == i)
			{
				shouldContinue = true;
			}
		}

		if (shouldContinue) continue;
		int copyFromNeuron = rand() % (int)( ceil(nextGenerationDescendants / 2) );

		neuralNetwork[i].Copy( neuralNetwork[ theBestNetworksIds[copyFromNeuron] ] );
	}
}

void LearningNeuralNetwork::MutateAllNetworks()
{
	for (int i = 0; i < ammountOfChildren; i++)
	{
		neuralNetwork[i].Mutate();
	}
}
