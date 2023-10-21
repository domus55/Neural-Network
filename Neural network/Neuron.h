#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

class Neuron
{
public:
	Neuron(int amountOfWeights);
	Neuron(Neuron&& n) noexcept;
	Neuron(const Neuron& n);
	///<summary>
	///Sets neurone value
	///</summary>
	void Input(float value);
	///<summary>
	///Mutates weights and bias
	///</summary>
	void Mutate();
	///<summary>
	///Randomly mixes weights and bias with this of an other neuron
	///</summary>
	void Merge(Neuron neuron2);
	void SetMutationRate(float rate);
	///<summary>
	///Returns value of 'i' the neuron connected to the right
	///</summary>
	float Output(int number);
	///<summary>
	///Returns value of this neuron
	///</summary>
	float Output();
	void Copy(Neuron neuron2);
	~Neuron();

private:
	float mutationRate = 0.05;
	float value;
	float *weight;
	float bias;
	int amountOfWeights;
	///<summary>
	///Sets random values to all weights
	///Used only when neuron is created
	///</summary>
	void MutateAllWeights();
	///<summary>
	///Mutates weights depenging on mutationRate
	///</summary>
	void MutateWeights();
	void MutateBias();
};

