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

void c_neural_net::calcuOut(){
	for (int i = 0; i < num_neurons_hidden_layer; i++)
	{
		double t = 0;
		for (int j = 0; j < num_inputs; j++) t += weight[1][j][i] * out[0][j];
		t += b[1][i];
		out[1][i] = sigmoid(t);
	}

	for (int i = 0; i < num_outputs; i++)
	{
		double t = 0;
		for (int j = 0; j < num_neurons_hidden_layer; j++)
			t += weight[2][j][i] * out[1][j];
		t += b[2][i];
		out[2][i] = sigmoid(t);
	}
}

std::vector<double> c_neural_net::ResOut(int x[]){
	for (int i = 0; i < num_inputs; i++) out[0][i] = x[i];
	calcuOut();
	std::vector<double> v;
	for (int i = 0; i < num_outputs; i++)
		v.push_back(out[2][i]);
	return v;
}

void c_neural_net::train(int x[], int d[]){
	for (int i = 0; i < num_inputs; ++i) out[0][i] = x[i];
	while (true){
		calcuOut();
	}
}