#pragma once 

#include <iostream>
#include <vector>

struct s_neuron{
	int num_inputs;						//the numbers of input of every neuron
	std::vector<double> vec_weight;		//the  weight of every input
	s_neuron(int num);
};


