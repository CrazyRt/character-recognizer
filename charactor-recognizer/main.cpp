#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL\Fl_Box.H>
#include <FL\Fl_Input.H>
#include <FL\Fl_Double_Window.H>
#include "neural_net.h"
#include <map>
using namespace std;


const int MAX_INPUT = 300;
const int num_char = 26;
const int level = 6;
int x[MAX_INPUT];

int xx[10000][MAX_INPUT];
int d[10000][MAX_INPUT];
char true_value;
int train_sum = 0;


Fl_Button*  ss[level][level];
map<char, int> char_to_num;
c_neural_net neuralNet(level*level, 30, num_char);

const char no_to_char[num_char] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M', 'N', 'O', 'P',
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

map<void*, int> get_no;



void train_cb(Fl_Widget* o, void* v) {
	cout << "example" << train_sum << endl;
	for (int i = 0; i < MAX_INPUT; ++i) xx[train_sum][i] = x[i];
	Fl_Input* i = (Fl_Input*)v;
	true_value = *(i->value());
	for (int i = 0; i < num_char; ++i) d[train_sum][i] = 0;
	d[train_sum][char_to_num[true_value]] = 1;
	neuralNet.train(xx[train_sum], d[train_sum]);
	cout << true_value << char_to_num[true_value] << endl;
	neuralNet.save("wt.ini");
	++train_sum;
}


void trainall_cb(Fl_Widget* o, void* v) {
	ifstream eg("example.ini");
	eg >> train_sum;
	cout << train_sum << endl;
	for (int i = 0; i < train_sum; ++i){
		for (int j = 0; j < level*level; ++j) eg >> xx[i][j];
		for (int j = 0; j < num_char; ++j) eg >> d[i][j];
	}
	cout << train_sum << endl;
	for (int i = 0; i < train_sum; ++i)	{ 
		for (int j = 0; j < level; ++j) {
			for (int k = 0; k < level; ++k) cout << xx[i][level*j+k] << " ";
			cout << endl;
		}
		for (int k = 0; k < num_char; ++k) if (d[i][k] == 1) cout << no_to_char[k]<<"example:"<<i;
		cout << endl;
		neuralNet.train(xx[i], d[i]);
	}
	
	neuralNet.save("wt.ini");

}

void recog_cb(Fl_Widget* o, void* v=0){
	
	for (int i = 0; i < level; ++i) {
		for (int j = 0; j < level; ++j) cout << x[i*level+j]<<" ";
		cout << endl;
	}
	vector<double> ans = neuralNet.ResOut(x);
	for (int i = 0; i < num_char; ++i)
		cout << no_to_char[i] << " " << ans[i] << endl;
}

void clr_cb(Fl_Widget* o, void* v) {
	for (int i = 0; i < level; ++i)
		for (int j = 0; j < level; ++j){
			ss[i][j]->clear();
			ss[i][j]->label("");
			x[i * level + j] = 0;

		}
}
void ld_cb(Fl_Widget* o, void* v=0) {
	neuralNet.load("wt.ini");
}

void sv_cb(Fl_Widget* o, void* v=0) {
	neuralNet.save("wt.ini");
	ofstream eg("example.ini");
	eg << train_sum<<endl;
	for (int i = 0; i < train_sum; ++i){
		for (int j = 0; j < level; ++j){
			for (int k = 0; k < level; ++k)	eg << xx[i][j*level+k] << " ";
			eg << endl;
		}
		for (int j = 0; j < num_char; ++j) eg << d[i][j] << " ";
		eg << endl;
	}
}

void exit_cb(Fl_Widget* o, void* v = 0) {
	exit(0);
}


void s_cb(Fl_Widget* o, void* v = 0){
	Fl_Button* b = (Fl_Button*)o;
	int t = get_no[b];
	if (x[t] == 1) { 
		b->label("");
		x[t] = 0;
	}
	else {
		b->label("1");
		x[t] = 1;
	}
	
	cout << x[t]<<"  "<<t<<endl;
}



int main() {
	for (int i = 0; i < num_char; ++i) char_to_num[no_to_char[i]] = i;
	

	//for (int i = 0; i < train_sum; ++i)	{
	//	for (int j = 0; j < level; ++j) {
	//		for (int k = 0; k < level; ++k) cout << xx[i][level*j + k] << " ";
	//		cout << endl;
	//	}
	//	for (int j = 0; j < num_char; ++j) cout << d[i][j] << " ";
	//	cout << endl;
	//}

	neuralNet.load("wt.ini");
	Fl_Double_Window win(1000, 800,"recognizer");
	int* val=new int(0);
	win.begin();
	Fl_Input *inpu = new Fl_Input(100, 10, 100, 30, "true value");
	Fl_Button *tra = new Fl_Button(10, 50, 100, 30, "train");
	Fl_Button *clr = new Fl_Button(210, 50, 100, 30, "clear");
	Fl_Button *reco = new Fl_Button(110, 50, 100, 30, "recognize");
	Fl_Button *exit = new Fl_Button(510, 50, 100, 30, "exit");
	Fl_Button *sv = new Fl_Button(310, 50, 100, 30, "save");
	Fl_Button *traA = new Fl_Button(410, 50, 100, 30, "train all");
	
	for (int i = 0; i < level; ++i)
		for (int j = 0; j < level; ++j){
			for (int k = 0; k < 10000; ++k) xx[k][i*level + j] = 0;
			ss[i][j] = new Fl_Button(200 + 30 * j, 200 + 30 * i, 30, 30, "");
			ss[i][j]->type(FL_TOGGLE_BUTTON);
			ss[i][j]->clear();
			ss[i][j]->label("");
			get_no[ss[i][j]] = i * level + j;
			
		}
	for (int i = 0; i < level; ++i)
		for (int j = 0; j < level; ++j){
			ss[i][j]->callback(s_cb, val);
		}


	
	reco->callback(recog_cb);
	clr->callback(clr_cb, ss);
	exit->callback(exit_cb);
	sv->callback(sv_cb);
	tra->callback(train_cb, inpu);
	traA->callback(trainall_cb);
	win.end();
	win.show();
	return Fl::run();
}