#pragma once
#include "Neuron.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class NeuronTest : public testing::TestWithParam<int> {};

TEST_P(NeuronTest, Bias)
{
	int numOfWeights = GetParam();
	Neuron n(numOfWeights);

	EXPECT_GE(n.Output(), -1);
	EXPECT_LE(n.Output(), 1);
}

TEST_P(NeuronTest, Weight)
{
	int numOfWeights = GetParam();
	Neuron n(numOfWeights);

	float startBias = n.Output();
	n.Input(1);
	float expectValue = (n.Output(0) - startBias) * 2 + startBias;
	n.Input(2);

	EXPECT_FLOAT_EQ(expectValue, n.Output(0));
}

TEST(NeuronTest, Mutate)
{
	Neuron n(1);
	n.SetMutationRate(1);
	n.Input(1);

	float beforeMutationBias = n.Output();
	float beforeMutationWeight = n.Output(0) - beforeMutationBias;
	n.Mutate();
	float afterMutationBias = n.Output();
	float afterMutationWeight = n.Output(0) - afterMutationBias;

	EXPECT_NE(beforeMutationBias, afterMutationBias);
	EXPECT_NE(beforeMutationWeight, afterMutationWeight);
}

TEST_P(NeuronTest, Copy)
{
	auto in = GetParam();
	Neuron orginal(in);
	Neuron copy(in);

	copy.Copy(orginal);
	orginal.Input(0);
	orginal.Input(0);

	EXPECT_EQ(orginal.Output(), copy.Output());

	orginal.Input(1);
	copy.Input(1);

	EXPECT_EQ(orginal.Output(0), copy.Output(0));
}

INSTANTIATE_TEST_SUITE_P(
	MyInstantiation, NeuronTest,
	testing::Values(1, 2, 3)
);