#include "Neuron.h"

Neuron::Neuron(int amountOfWeights)
	:amountOfWeights(amountOfWeights)
{
	value = 0;
	weight = new float[amountOfWeights];
	MutateAllWeights();
	bias = (rand() % 10000 - 5000) / 5000.0;
}

Neuron::Neuron(Neuron&& n) noexcept
{
	value = 0;
	amountOfWeights = n.amountOfWeights;
	weight = n.weight;
	for (int i = 0; i < amountOfWeights; i++)
	{
		weight[i] = n.weight[i];
	}
	bias = n.bias;
	n.weight = nullptr;
}

Neuron::Neuron(const Neuron& n)
{
	value = 0;
	amountOfWeights = n.amountOfWeights;
	weight = new float[amountOfWeights];
	for (int i = 0; i < amountOfWeights; i++)
	{
		weight[i] = n.weight[i];
	}
	bias = n.bias;
}

void Neuron::Input(float value)
{
	this->value = value;
}

void Neuron::Mutate()
{
	MutateWeights();
	MutateBias();
}

void Neuron::MutateWeights()
{
	for (int i = 0; i < amountOfWeights; i++)
	{
		if (rand() % 1000 / 1000.0 < mutationRate)
		{
			weight[i] = (rand() % 10000 - 5000) / 5000.0;
		}
	}
}

void Neuron::MutateBias()
{
	if (rand() % 1000 / 1000.0 < mutationRate)
	{
		bias = (rand() % 10000 - 5000) / 5000.0;
	}
}

void Neuron::MutateAllWeights()
{
	for (int i = 0; i < amountOfWeights; i++)
	{
		weight[i] = (rand() % 10000 - 5000) / 5000.0;
	}
}

void Neuron::Merge(Neuron neuron2)
{
	if (rand() % 2 == 0) bias = (bias + neuron2.bias) / 2.0;

	for (int i = 0; i < amountOfWeights; i++)
	{
		//if (rand() % 2 == 0) weight[i] = neuron2.weight[i];
		weight[i] = (weight[i] + neuron2.weight[i]) / 2.0;
	}
}

void Neuron::SetMutationRate(float percentage)
{
	this->mutationRate = percentage;
}

float Neuron::Output(int number)
{
	return value * weight[number] + bias;
}

float Neuron::Output()
{
	return value + bias;
}

void Neuron::Copy(Neuron neuron2)
{
	bias = neuron2.bias;

	for (int i = 0; i < amountOfWeights; i++)
	{
		weight[i] = neuron2.weight[i];
	}
}

Neuron::~Neuron()
{
	delete[] weight;
}
