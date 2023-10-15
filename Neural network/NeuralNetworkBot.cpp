#include "NeuralNetworkBot.h"

void NeuralNetworkBot::Create(unsigned int layer1, unsigned int layer2, unsigned int layer3, unsigned int layer4, unsigned int layer5, unsigned int layer6)
{
	nextGenerationDescendants = (int)(nextGenerationDescendantsPercentage * ammountOfChildrens);
	theBestNetworksIds = new int[nextGenerationDescendants];

	for (int i = 0; i < nextGenerationDescendants; i++)
	{
		theBestNetworksIds[i] = 0;
	}

	for (int i = 0; i < ammountOfChildrens; i++)
	{
		NeuralNetwork n(layer1, layer2, layer3, layer4, layer5, layer6);
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

void NeuralNetworkBot::SetNextGenerationDescendantsPercentage(float rate)
{
	nextGenerationDescendantsPercentage = rate;
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
		neuralNetwork[activeNetwork].WinRate = (allPoints + win) / (float)(activeTest + 1);
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

	//std::cout << "desc: " << nextGenerationDescendants << "\n";
	//std::cout << "size: " << neuralNetwork.size() << "\n";

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

		//std::cout << "win race: " << maxWinRate << "\n";

		//std::cout << neuralNetwork[theBestNetworksIds[i]].WinRate << "\n";
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
			//std::cout << neuralNetwork[i].WinRate << "\n";
			//std::cout << neuralNetwork[theBestNetworksIds[i]].WinRate << "\n";
			//neuralNetwork[theBestNetworksIds[nextGenerationDescendants - i - 1]];


			neuralNetwork[theBestNetworksIds[i]].Merge(neuralNetwork[theBestNetworksIds[nextGenerationDescendants - i - 1]]);
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
		
		
		//std::cout << neuralNetwork[theBestNetworksIds[copyFromNeuron]].WinRate <<"\n";
		neuralNetwork[i].Copy( neuralNetwork[ theBestNetworksIds[copyFromNeuron] ] );
	}
}

void NeuralNetworkBot::MutateAllNetworks()
{
	for (int i = 0; i < ammountOfChildrens; i++)
	{
		//std::cout << neuralNetwork[i].WinRate << "\n";
		neuralNetwork[i].Mutate();
	}
}
