#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"

class NeuralNetwork
{
public:
	float WinRate = 0;

	NeuralNetwork(unsigned int layer1, unsigned int layer2);
	void Copy(NeuralNetwork neuralNetwork2);
	void Input(int neuron, int value);
	void CalculateTheOutput();
	float Output(int neuron);
	void SetMutationRate(float rate);
	void Merge(NeuralNetwork neuralNetwork2);
	void Mutate();

private:
	std::vector <Neuron> neuron;
	float mutationRate = 0.05;
	int layer1 = 0;
	int layer2 = 0;
	int layer3 = 0;
	int layer4 = 0;
	void AddNeurons(int ammount, int ammountOfWeights);
	void CalculateNextLayerValue(int layer1, int layer2, int firstNeuronId);
};

