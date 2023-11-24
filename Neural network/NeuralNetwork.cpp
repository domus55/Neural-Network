#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::initializer_list<unsigned int> layers)
{
	int numOfLayers = layers.size();
	layer.resize(numOfLayers);

	int neuronsInTotal = 0;
	int i = 0;
	for (auto numOfNeurons : layers)
	{
		this->layer[i] = numOfNeurons;
		neuronsInTotal += numOfNeurons;

		if (i + 1 == numOfLayers) //if it's the last layer
		{
			AddNeurons(numOfNeurons, 1);
		}
		else
		{
			AddNeurons(numOfNeurons, layers.begin()[i + 1]);
		}

		i++;
	}

	neuron.reserve(neuronsInTotal);
}

void NeuralNetwork::Copy(NeuralNetwork neuralNetwork2)
{
	for (unsigned int i = 0; i < neuron.size(); i++)
	{
		neuron[i].Copy(neuralNetwork2.neuron[i]);
	}
}

void NeuralNetwork::AddNeurons(int amount, int amountOfWeights)
{
	for (int i = 0; i < amount; i++)
	{
		Neuron newNeuron(amountOfWeights);
		newNeuron.SetMutationRate(mutationPercentage);
		neuron.push_back(std::move(newNeuron));
	}
}

void NeuralNetwork::Input(int neuron, float value)
{
	this->neuron[neuron].Input(value);
}

void NeuralNetwork::CalculateTheOutput()
{
	int sumOfNeuronsBefore = 0;
	for (unsigned int i = 0; i < layer.size() - 1; i++)
	{
		CalculateNextLayerValue(layer[i], layer[i + 1], sumOfNeuronsBefore);
		sumOfNeuronsBefore += layer[i];
	}

	//show values and weights of the first 3 layers
	/*if (rand() % 50000 == 0) {

		std::cout << "\n";

		for (int i = 0; i < layer1; i++)
		{
			std::cout << neuron[i].Output() << "\n";
			for (int j = 0; j < layer2; j++)
			{
				std::cout << "\t" << neuron[i].Output(j) << "\n";
			}
			std::cout << "\n";
		}

		std::cout << "\n--------------------\n";

		for (int i = 0; i < layer2; i++)
		{
			std::cout << neuron[i + layer1].Output() << "\n";
			for (int j = 0; j < layer3; j++)
			{
				std::cout << "\t" << neuron[i + layer1].Output(j) << "\n";
			}
			std::cout << "\n";
		}

		std::cout << "\n";

		for (int i = 0; i < layer3; i++)
		{
			std::cout << neuron[i + layer1 + layer2].Output() << " ";
		}

		std::cout << "\n\n";
	}*/
}

float NeuralNetwork::Output(int neuronId)
{
	int sumOfNeuronsBefore = 0;
	for (unsigned int i = 0; i < layer.size() - 1; i++)
	{
		sumOfNeuronsBefore += layer[i];
	}

	return neuron[sumOfNeuronsBefore + neuronId].Output();
}

void NeuralNetwork::SetMutationRate(float rate)
{
	this->mutationPercentage = rate;
}

void NeuralNetwork::Merge(NeuralNetwork neuralNetwork2)
{
	WinRate = (WinRate + neuralNetwork2.WinRate) / 2;

	for (unsigned int i = 0; i < neuron.size(); i++)
	{
		neuron[i].Merge(neuralNetwork2.neuron[i]);
	}
}

void NeuralNetwork::Mutate()
{
	for (unsigned int i = 0; i < neuron.size(); i++)
	{
		neuron[i].SetMutationRate( (1 - WinRate) * mutationPercentage );
		neuron[i].Mutate();
	}
}

void NeuralNetwork::CalculateNextLayerValue(int prevLayerSize, int nextLayerSize, int firstNeuronIndex)
{
	for (int i = 0; i < nextLayerSize; i++)
	{
		float sum = 0;
		for (int j = 0; j < prevLayerSize; j++)
		{
			sum += neuron[j + firstNeuronIndex].Output(i);
		}

		neuron[prevLayerSize + firstNeuronIndex + i].Input(sum);
	}
}


