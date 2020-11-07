#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"

class NeuralNetwork
{
public:
	float WinRate = 0;

	NeuralNetwork(int layer1, int layer2, int layer3 = 0, int layer4 = 0, int layer5 = 0, int layer6 = 0);
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
	int layer5 = 0;
	int layer6 = 0;
	void AddNeurons(int ammount, int ammountOfWeights);
	void CalculateNextLayerValue(int layer1, int layer2, int firstNeuronId);
};

