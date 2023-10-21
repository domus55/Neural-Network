#pragma once

#include <vector>
#include <math.h>
#include "NeuralNetwork.h"

//TODO: consider changing class name
class LearningNeuralNetwork
{
public:
	static int generation;
	void Create(std::initializer_list<unsigned int> layers);
	void SetAmmountOfChildren(int ammount);
	void SetMutationRate(float rate);
	///<summary>
	/// By increasing test ammount neural network will be more precise, but will learn slower. Set it to 1 if there is nothing random in it's task
	///</summary>
	void SetTestAmmount(int ammount);

	///<summary>
	/// Percentage of all children that will be the base to next generation
	///</summary>
	void SetNextGenerationDescendantsPercentage(float rate);
	///<summary>
	/// Use this after each game to let neural network know, how good it was, pass value between 0-1
	///</summary>
	void Update(float win);
	void Input(int neuronId, float value);
	void CalculateOutputs();
	float Output(int neuronId);
private:
	std::vector <NeuralNetwork> neuralNetwork;
	int ammountOfChildren = 100;
	float mutationRate = 0.05;
	float nextGenerationDescendantsPercentage = 0.1;
	int nextGenerationDescendants = 0;
	int testAmmount = 1;
	int activeTest;
	//Neural network which is reciving inputs, and giving outputs
	int activeNetwork = 0;
	std::vector <int> theBestNetworksIds;

	void NextGeneration();
	void FindTheBestNetworks();
	void MergeTheBestNetworks();
	void CopyTheBestNetworksToAllNetworks();
	void MutateAllNetworks();
};

