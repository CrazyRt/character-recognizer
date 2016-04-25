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
		double p_error = get_error(d);
		get_delta(d);
		update();
		if (p_error < max_error) break;
	}
}

double c_neural_net::get_error(int d[]){
	double ans = 0;
	for (int i = 0; i < num_outputs; i++)
		ans += 0.5 * (out[2][i] - d[i]) * (out[2][i] - d[i]);
	return ans;
}

void c_neural_net::get_delta(int d[]){
	for (int i = 0; i < num_neurons_hidden_layer; i++){
		double dta = 0;
		for (int j = 0; j < num_outputs; j++)
			dta += weight[2][i][j] * delta[2][j];
		delta[1][i] = dta * out[1][i] * (1 - out[1][i]) ;
	}
	for (int i = 0; i < num_outputs; i++)
		delta[2][i] = (out[2][i] - d[i]) * out[2][i] * (1 - out[2][i]) ;
	
}

void c_neural_net::update(){
	for (int i = 0; i < num_neurons_hidden_layer; i++)
		for (int j = 0; j < num_outputs; j++)
			weight[2][i][j] -= eta_w * delta[2][j] * out[1][i];
	
	for (int i = 0; i < num_outputs; i++)	b[2][i] -= eta_b * delta[2][i];
  
	for (int i = 0; i < num_inputs; i++)
		for (int j = 0; j < num_neurons_hidden_layer; j++)
			weight[1][i][j] -= eta_w * delta[1][j] * out[0][i];
	
	for (int i = 0; i < num_neurons_hidden_layer; i++)	b[1][i] -= eta_b * delta[1][i];

}

void c_neural_net::save(std::string str){
	std::string src =  str;
	std::ofstream ofile(src);
	ofile << num_inputs<<std::endl;
	ofile << num_outputs << std::endl;
	ofile << num_neurons_hidden_layer << std::endl;
	for (int i = 0; i < num_neurons_hidden_layer; i++){
		for (int j = 0; j < num_inputs; j++) ofile << weight[1][j][i]<<" ";
		ofile << b[1][i] << " ";
	}

	for (int i = 0; i < num_outputs; i++){
		for (int j = 0; j < num_neurons_hidden_layer; j++)	ofile << weight[2][j][i] << " ";
		ofile << b[2][i] << " ";
	}
}

void c_neural_net::load(std::string str){
	std::string src =  str;
	std::ifstream ofile(src);
	ofile >> num_inputs ;
	ofile >> num_outputs ;
	ofile >> num_neurons_hidden_layer ;
	for (int i = 0; i < num_neurons_hidden_layer; i++){
		for (int j = 0; j < num_inputs; j++) ofile >> weight[1][j][i] ;
		ofile >> b[1][i] ;
	}

	for (int i = 0; i < num_outputs; i++){
		for (int j = 0; j < num_neurons_hidden_layer; j++)	ofile >> weight[2][j][i];
		ofile >> b[2][i];
	}
}