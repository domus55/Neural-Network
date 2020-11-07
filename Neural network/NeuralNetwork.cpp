#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int layer1, int layer2, int layer3, int layer4, int layer5, int layer6)
{
	srand(time(NULL));

	AddNeurons(layer1, layer2);

	if(layer3 == 0) AddNeurons(layer2, 1);
	else
	{
		AddNeurons(layer2, layer3);
		if (layer4 == 0) AddNeurons(layer3, 1);
		else
		{
			AddNeurons(layer3, layer4);
			if (layer5 == 0) AddNeurons(layer4, 1);
			else
			{
				AddNeurons(layer4, layer5);
				if (layer6 == 0) AddNeurons(layer5, 1);
				else
				{
					AddNeurons(layer5, layer6);
					AddNeurons(layer6, 1);
				}
			}
		}
	}

	this->layer1 = layer1;
	this->layer2 = layer2;
	this->layer3 = layer3;
	this->layer4 = layer4;
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
	if(layer3 != 0) CalculateNextLayerValue(layer2, layer3, layer1);
	if(layer4 != 0) CalculateNextLayerValue(layer3, layer4, layer1 + layer2);
	if(layer5 != 0) CalculateNextLayerValue(layer4, layer5, layer1 + layer2 + layer3);
	if(layer6 != 0) CalculateNextLayerValue(layer5, layer6, layer1 + layer2 + layer3 + layer4);
}

float NeuralNetwork::Output(int neuronId)
{
	if(layer3 == 0) return neuron[layer1 + neuronId].Output();
	if(layer4 == 0) return neuron[layer1 + layer2 + neuronId].Output();
	if(layer5 == 0) return neuron[layer1 + layer2 + layer3 + neuronId].Output();
	if(layer6 == 0) return neuron[layer1 + layer2 + layer3 + layer4 + neuronId].Output();
	else			return neuron[layer1 + layer2 + layer3 + layer4 + layer5 + neuronId].Output();
	
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


