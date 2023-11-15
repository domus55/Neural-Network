#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"

class NeuralNetwork
{
public:
	float WinRate = 0;
	NeuralNetwork(std::initializer_list<unsigned int> layers);
	void Copy(NeuralNetwork neuralNetwork2);
	void Input(int neuron, float value);
	//You need to you is before calling Output(int) method
	void CalculateTheOutput();
	//Get output from neuron
	float Output(int neuron);
	void SetMutationRate(float rate);
	void Merge(NeuralNetwork neuralNetwork2);
	void Mutate();

private:
	std::vector <Neuron> neuron;
	float mutationRate;
	//Ammount of neurons in each layer
	std::vector <unsigned int> layer;
	void AddNeurons(int ammount, int ammountOfWeights);
	void CalculateNextLayerValue(int prevLayerSize, int nextLayerSize, int firstNeuronIndex);
};

