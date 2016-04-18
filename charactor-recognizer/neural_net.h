#pragma once

#include "neural_layer.h"

class c_neural_net{
private:
	int num_inputs;
	int num_outputs;
	int num_hidden_layers;
	std::vector<s_neural_layer> vec_layers;
public:
};