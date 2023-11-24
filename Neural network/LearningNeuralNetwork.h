#pragma once

#include <vector>
#include <math.h>
#include "NeuralNetwork.h"
#include <optional>

class LearningNeuralNetwork
{
public:
	LearningNeuralNetwork(std::initializer_list<unsigned int> layers, unsigned int amountOfChildren = 200);

	///<summary>
	/// Optional method, you can call it rigt after creating LearningNeuralNetwork to set argument
	/// nextGenerationDescendantsPercentage - Percentage of descendants to pick while choosing which networks to merge
	/// mutationPercentage - How much neural network should mutate
	///</summary>
	void SetArguments(float nextGenerationDescendantsPercentage, float mutationPercentage);

	///<summary>
	/// By increasing test amount neural network will be more precise, but will learn slower. Set it to 1 if there is nothing random in it's task
	///</summary>
	void SetTestAmount(unsigned int amount);

	///<summary>
	/// Use this after each game to let neural network know, how good it was, pass value between 0-1
	///</summary>
	void Update(float winPercentage);
	void Input(unsigned int neuronId, float value);

	///<summary>
	/// Use after providing all inputs and before calling Output() method to get correct outputs
	///</summary>
	void CalculateOutputs();
	float Output(unsigned int neuronId);

	///<summary>
	/// After calling that method LearningNeuralNetwork stops improving and 
	/// uses the neural network with a highest winRate
	/// Call after winRate is satysfying
	///</summary>
	void SetFinishLearning(bool finish);
	bool GetFinishLearning();
	int GetGeneration();
	float GetBestWinRate();

private:
	std::vector <NeuralNetwork> neuralNetwork;
	NeuralNetwork bestNeuralNetwork;
	int generation = 1;
	unsigned int amountOfChildren = 100;
	float mutationPercentage = 0.05f;
	float nextGenerationDescendantsPercentage = 0.1f;
	unsigned int nextGenerationDescendants = 0;
	unsigned int testAmount = 1;
	unsigned int activeTest;
	//Neural network which is reciving inputs, and giving outputs
	unsigned int activeNetwork = 0;
	bool finishLearning = false;

	void NextGeneration();
	//Finds best networks, merges them and populates whole next gen with them
	void NeuralNetworksEvolve();
	void MutateAllNetworks();
};

