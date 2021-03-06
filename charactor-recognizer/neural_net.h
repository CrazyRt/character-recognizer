#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define eta_w 0.004
#define eta_b 0.001
#define max_layers 10
#define max_neurons 102
#define max_error 0.02

inline double sigmoid(double x){ return double(1) / (1 + exp(-x)); };

class c_neural_net{
private:
	int num_inputs,num_outputs;
	int num_neurons_hidden_layer;
	
	double b[3][max_neurons];
	double weight[3][max_neurons][max_neurons];
	double out[3][max_neurons];
	double delta[3][max_neurons];

public:
	c_neural_net(int numInputs,int numOutputs,int num_neurons_hidden_layer);
	void load(std::string str);
	void save(std::string str);
	void train(int x[], int d[]);
	void calcuOut();
	void get_delta(int d[]);
	void update();
	double get_error(int d[]);
	std::vector<double> ResOut(int x[]);
};