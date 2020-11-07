#pragma once

#include <vector>
#include <math.h>
#include "NeuralNetwork.h"

class NeuralNetworkBot
{
public:
	void Create(unsigned int layer1, unsigned int layer2, unsigned int layer3 = 0, unsigned int layer4 = 0, unsigned int layer5 = 0, unsigned int layer6 = 0);
	void SetAmmountOfChildrens(int ammount);
	void SetMutationRate(float rate);
	void SetTestAmmount(int ammount);

	///<summary>
	/// How many percentage of all children will be base to next generation
	///</summary>
	void SetNextGenerationDescendantsRate(float rate);

	///<summary>
	/// Use this after all win/lose
	///</summary>
	void Update(float win);
	void Input(int neuronId, float value);
	void CalculateOutputs();
	float Output(int neuronId);
private:
	std::vector <NeuralNetwork> neuralNetwork;
	int ammountOfChildrens = 100;
	float mutationRate = 0.05;
	float nextGenerationDescendantsRate = 0.1;
	float nextGenerationDescendants = 0;
	int testAmmount = 1;
	int activeTest;
	//Neural network which is reciving inputs, and giving outputs
	int activeNetwork = 0;
	int * theBestNetworksIds;

	void NextGeneration();
	void FindTheBestNetworks();
	void MergeTheBestNetworks();
	void CopyTheBestNetworksToAllNetworks();
	void MutateAllNetworks();
};

