#include "neural_layer.h"

s_neural_layer::s_neural_layer(int num, int num_inputs){
	for (int i = 0; i < num; ++i) vec_neurons.push_back(s_neuron(num_inputs));
}