#include "neuron.h"

s_neuron::s_neuron(int num){
	num_inputs = num;
	for (int i = 0; i < num + 1; ++i) vec_weight.push_back(0);
}