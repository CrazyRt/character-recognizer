#pragma once

#include "neuron.h"

struct s_neural_layer{
	std::vector<s_neuron> vec_neurons;
	int num_neurons;
	s_neural_layer(int num,int num_inputs);
};