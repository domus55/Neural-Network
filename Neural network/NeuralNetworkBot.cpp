#include "NeuralNetworkBot.h"

void NeuralNetworkBot::Create(int layer1, int layer2)
{
	nextGenerationDescendants = (int)(nextGenerationDescendantsRate * ammountOfChildrens);
	theBestNetworksIds = new int[nextGenerationDescendants];

	for (int i = 0; i < nextGenerationDescendants; i++)
	{
		theBestNetworksIds[i] = 0;
	}

	for (int i = 0; i < ammountOfChildrens; i++)
	{
		NeuralNetwork n(layer1, layer2);
		n.SetMutationRate(mutationRate);
		neuralNetwork.push_back(n);
	}
}

void NeuralNetworkBot::SetAmmountOfChildrens(int ammount)
{
	ammountOfChildrens = ammount;
}

void NeuralNetworkBot::SetMutationRate(float rate)
{
	mutationRate = rate;
}

void NeuralNetworkBot::SetTestAmmount(int ammount)
{
	testAmmount = ammount;
}

void NeuralNetworkBot::SetNextGenerationDescendantsRate(float rate)
{
	nextGenerationDescendantsRate = rate;
}

void NeuralNetworkBot::Update(float win)
{
	if (activeTest == 0)
	{
		neuralNetwork[activeNetwork].WinRate = win;
	}
	else
	{
		float allPoints = neuralNetwork[activeNetwork].WinRate * activeTest;
		neuralNetwork[activeNetwork].WinRate = (allPoints + win) / (activeTest + 1);
	}
	
	activeTest++;

	if (activeTest >= testAmmount)
	{
		activeNetwork++;
		activeTest = 0;
	}
	

	if (activeNetwork >= ammountOfChildrens)
	{
		activeNetwork = 0;
		NextGeneration();
	}
}

void NeuralNetworkBot::Input(int neuronId, float value)
{
	neuralNetwork[activeNetwork].Input(neuronId, value);
}

void NeuralNetworkBot::CalculateOutputs()
{
	neuralNetwork[activeNetwork].CalculateTheOutput();
}

float NeuralNetworkBot::Output(int neuronId)
{
	return neuralNetwork[activeNetwork].Output(neuronId);
}

void NeuralNetworkBot::NextGeneration()
{
	FindTheBestNetworks();
	MergeTheBestNetworks();
	CopyTheBestNetworksToAllNetworks();
	MutateAllNetworks();
}

void NeuralNetworkBot::FindTheBestNetworks()
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

void NeuralNetworkBot::MergeTheBestNetworks()
{
	for (int i = 0; i < nextGenerationDescendants / 2; i++)
	{
		if (i != nextGenerationDescendants - i - 1)
		{
			//std::cout << i << "\t\t" << nextGenerationDescendants - i - 1 << "\n";

			neuralNetwork[i].Merge(neuralNetwork[nextGenerationDescendants - i - 1]);
		}
	}
}

void NeuralNetworkBot::CopyTheBestNetworksToAllNetworks()
{
	for (int i = 0; i < ammountOfChildrens; i++)
	{
		bool shouldContinue = false;
		for (int j = 0; j < nextGenerationDescendants; j++)
		{
			if (theBestNetworksIds[j] == i) shouldContinue = true;
		}

		if (shouldContinue) continue;
		int copyFromNeuron = rand() % (int)( ceil(nextGenerationDescendants / 2) );
		
		neuralNetwork[i].Copy( neuralNetwork[ theBestNetworksIds[copyFromNeuron] ] );
	}
}

void NeuralNetworkBot::MutateAllNetworks()
{
	for (int i = 0; i < ammountOfChildrens; i++)
	{
		neuralNetwork[i].Mutate();
	}
}
