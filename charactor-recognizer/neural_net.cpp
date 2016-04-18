#include "neural_net.h"


c_neural_net::c_neural_net(int nInput, int nOutputs,int numNeuronsHiddenLayer){
	num_inputs = nInput;
	num_outputs = nOutputs;
	num_neurons_hidden_layer = numNeuronsHiddenLayer;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < max_neurons; ++j){
			for (int k = 0; k < max_neurons; ++k) weight[i][j][k] = 2.0 * rand() / RAND_MAX - 1.0;
			b[i][j] = 2.0 * rand() / RAND_MAX - 1.0;
		}
}

void c_neural_net::train(int x[], int d[]){

}