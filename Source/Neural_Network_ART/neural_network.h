#pragma once

#include "../Neural_Network_ART/Eigen/src/Core/Matrix.h"
#include <vector>

constexpr auto LEARNING_RATE = 0.01;

class neural_network
{
public:
	// enum for two modes of activation
	enum Activation { TANH, SIGMOID } mActivation;
	// network learning rate
	double mLearningRate;
	// network layers architecture (input-hidden-output) 
	std::vector<int> mArchitecture;
	// network layers vectors
	std::vector<RowVectorXd*> mNeurons;
	// neurons' output errors
	std::vector<RowVectorXd*> mErrors;
	// connections' weights
	std::vector<MatrixXd*> mWeights;
	// confusion matrix
	MatrixXd* mConfusion;

	// constructors
	neural_network();
	~neural_network();
	neural_network(
		std::vector<int> architecture,
		double learningRate = LEARNING_RATE,
		Activation = TANH);
	void init(
		std::vector<int> architecture,
		double learningRate = LEARNING_RATE,
		Activation = TANH);
	// load from file
	bool load(const char* file);

	// save to file
	void save(const char* file);

	// data forward propagation
	void forward(RowVectorXd& input);
	double activation(double x);

	// backward propagation of errors
	void backward(RowVectorXd& output);
	double activationDerivative(double x);

	// train the neural network given an input
	void train(RowVectorXd& input, RowVectorXd& output);

	// test the neural network given an input
	void test(RowVectorXd& input, RowVectorXd& output);

	void resetConfusion();
	void evaluate(RowVectorXd& output);
	void confusionMatrix(RowVectorXd*& precision, RowVectorXd*& recall);

	// get max output index
	int vote(double& value);
	int vote(RowVectorXd& v, double& value);

	// get last layer output
	double output(int col);

	// get output layer mean squere error
	double mse();
};