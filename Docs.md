# Learning Algorithm

This artificial neural network employs an evolutionary learning approach to enhance its results. Here's a quick explanation of how it works, assuming default values:
- Amount of Children: 200
- Descendants Percentage: 0.1
- Mutation Percentage: 0.05
- Test Amount: 1

It's important to note that we will discuss two different classes:
- **NeuralNetwork**: Neurons grouped in layers and connected with each other through weights.
- **LearningNeuralNetwork**: Manages the learning process; in our example, it contains 200 NeuralNetworks.

At the beginning, the LearningNeuralNetwork creates 200 NeuralNetworks with random weights and biases. By calling `Input(n, v)`, it passes input values to the first NeuralNetwork and retrieves output values in a similar fashion. After finishing the test you need to call `Update(winPercentage)`. The LearningNeuralNetwork stores `winPercentage` in the first NeuralNetwork. Now it starts passing input values and retrieving output from the next NeuralNetwork. This process continues until we call `Update(winPercentage)` 200 times (AmountOfChildren * TestAmount). Subsequently, the LearningNeuralNetwork initiates the creation of the next generation.
<br><br>
In this creation process, it identifies the top 10% (0.1) of the best NeuralNetworks based on `winPercentage`, which in our case amounts to the top 20 networks. It then merges these 20 networks to form 10 new merged networks. These 10 merged networks are copied to the entire population of 200 NeuralNetworks and undergo mutation by `mutationPercentage`. The testing process starts from the beginning.


# LearningNeuralNetwork documentation
#### LearningNeuralNetwork(std::initializer_list<unsigned int> layers, unsigned int amountOfChildren = 200)
Inputs: 
- layers: The first value indicates the number of neurons in the input layer, representing how many different inputs the network can distinguish. The last value represents the number of neurons in the output layer. All values in between define the number of neurons in each hidden layer. It needs at least 2 values (input and output layers).
- amountOfChildren: specifies how many children will be used in the learning process. The more, the better, but learning will also be slower.

#### void SetArguments(float descendantsPercentage, float mutationPercentage)
Inputs:
- descendantsPercentage: a value in range 0-1, indicates percentage of descendants used to create the next generation. Default value set in constructor is 0.1
- mutationPercentage: a value in range 0-1, indicates how much the neural network mutates

It's an optional method. If you don't call it LearningNeuralNetwork will use default values. Call it before learning process begins.
<hr>

#### void SetTestAmount(unsigned int amount)
Inputs:
- amount: the number of tests each network will be subjected to. Minimal value is 1.

By increasing the test amount neural network will be more precise, but will learn slower.
<hr>

#### void Update(float winPercentage)
Inputs:
- winPercentage: a value in range 0-1. Indicates the network's performance.

Call this method after you tested the network. It will create next generation after being called `amountOfChildren * testAmount` times.
<hr>

#### void Input(unsigned int neuronId, float value)
Inputs: 
- neuronId: the neuron to which you want to pass a value. It cannot be greater than the number of neurons in the input layer
- value: the value passed to the neuron
<hr>

#### void CalculateOutputs()
Call this method after passing all input values but before receiving outputs.
<hr>

#### float Output(unsigned int neuronId)
Inputs: 
- neuronId: the neuron from which you want to receive output. It cannot be greater than the number of neurons in the output layer

Return value:
- value of the `neuronId` neuron in the output layer
<hr>

#### void SetFinishLearning(bool finish);
Inputs:
- finish: set if LearningNeuralNetwork should finish learning

After calling `SetFinishLearning(true)` LearningNeuralNetwork will stop learning and creating new generations. From this moment it will use it's
best network to provide outputs. You can undo this by calling `SetFinishLearning(false)`. You can check the `finish` value by calling `GetFinishLearning()`
<hr>

#### bool GetFinishLearning()
Return value: 
- bool indicating if LearningNeuralNetwork has stopped learning

It will return true only after you call `SetFinishLearning(true)`.
<hr>

#### int GetGeneration();
Return value: 
- returns current generation number
<hr>

#### float GetBestWinRate();
Return value: 
- returns the `winPercentage` of the best NeuralNetwork