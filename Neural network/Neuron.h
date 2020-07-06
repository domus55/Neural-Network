#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

class Neuron
{
public:
	Neuron(int amountOfWeights);
	void Input(float value);
	void Mutate();
	void Merge(Neuron neuron2);
	void SetMutationRate(float rate);
	float Output(int number);
	float Output();
	void Copy(Neuron neuron2);

private:
	float mutationRate = 0.05;
	float value;
	float *weight;
	float bias;
	int amountOfWeights;

	void MutateAllWeights();
	///<summary>
	///mutates some percent of weights
	///</summary>
	void MutateWeights();
	void MutateBias();
};

