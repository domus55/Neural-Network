#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(unsigned int layer1, unsigned int layer2)
{
	srand(time(NULL));

	AddNeurons(layer1, layer2);
	AddNeurons(layer2, 1);
	this->layer1 = layer1;
	this->layer2 = layer2;
}

void NeuralNetwork::Copy(NeuralNetwork neuralNetwork2)
{
	for (int i = 0; i < neuron.size(); i++)
	{
		neuron[i].Copy(neuralNetwork2.neuron[i]);
	}
}

void NeuralNetwork::AddNeurons(int ammount, int ammountOfWeights)
{
	for (int i = 0; i < ammount; i++)
	{
		Neuron newNeuron(ammountOfWeights);
		newNeuron.SetMutationRate(mutationRate);
		neuron.push_back(newNeuron);
	}
}

void NeuralNetwork::Input(int neuron, int value)
{
	this->neuron[neuron].Input(value);
}

void NeuralNetwork::CalculateTheOutput()
{
	CalculateNextLayerValue(layer1, layer2, 0);
}

float NeuralNetwork::Output(int neuronId)
{
	return neuron[layer1 + neuronId].Output();
}

void NeuralNetwork::SetMutationRate(float rate)
{
	this->mutationRate = rate;
}

void NeuralNetwork::Merge(NeuralNetwork neuralNetwork2)
{
	WinRate = (WinRate + neuralNetwork2.WinRate) / 2;

	for (int i = 0; i < neuron.size(); i++)
	{
		neuron[i].Merge(neuralNetwork2.neuron[i]);
	}
}

void NeuralNetwork::Mutate()
{
	for (int i = 0; i < neuron.size(); i++)
	{
		neuron[i].SetMutationRate( (1 - WinRate) * mutationRate );
		neuron[i].Mutate();
	}
}

void NeuralNetwork::CalculateNextLayerValue(int layer1, int layer2, int firstNeuronId)
{
	float *suma = new float[layer2];

	for (int i = 0; i < layer2; i++)
	{
		suma[i] = 0;
	}

	for (int i = 0; i < layer2; i++)
	{
		for (int j = 0; j < layer1; j++)
		{
			suma[i] += neuron[j].Output(i);
		}

		neuron[layer1 + firstNeuronId + i].Input(suma[i]);
	}

	delete[]suma;
}


