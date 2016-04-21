#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL\Fl_Box.H>
#include <FL\Fl_Input.H>
#include <FL\Fl_Double_Window.H>
#include "neural_net.h"
#include <map>
using namespace std;


const int MAX_INPUT = 200;
const int num_char = 26;
const int level = 6;
int x[1000][MAX_INPUT];
int d[1000][MAX_INPUT];
char true_value;
int train_sum = 0;

Fl_Button*  ss[level][level];
map<char, int> char_to_num;
c_neural_net neuralNet(level*level, 30, num_char);

const char no_to_char[num_char] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M', 'N', 'O', 'P',
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

map<void*, int> get_no;



void train_cb(Fl_Widget* o, void* v) {

	Fl_Input* i = (Fl_Input*)v;
	true_value = *(i->value());
	for (int i = 0; i < num_char; ++i) d[train_sum][i] = 0;
	d[train_sum][char_to_num[true_value]] = 1;
	neuralNet.train(x[train_sum], d[train_sum]);
	cout << true_value << char_to_num[true_value] << endl;
	neuralNet.save("1.ini");
	++train_sum;
}


void trainall_cb(Fl_Widget* o, void* v) {

	for (int i = 0; i < train_sum;++i)	neuralNet.train(x[i], d[i]);
	
	neuralNet.save("1.ini");

}

void recog_cb(Fl_Widget* o, void* v=0){
	for (int i = 0; i < level; ++i) {
		for (int j = 0; j < level; ++j) cout << x[train_sum][i*level+j]<<" ";
		cout << endl;
	}
	vector<double> ans = neuralNet.ResOut(x[train_sum]);
	for (int i = 0; i < num_char; ++i)
		cout << no_to_char[i] << " " << ans[i] << endl;
}

void clr_cb(Fl_Widget* o, void* v) {
	for (int i = 0; i < level; ++i)
		for (int j = 0; j < level; ++j){
			ss[i][j]->clear();
			ss[i][j]->label("");
			x[train_sum][i * level + j] = 0;

		}
}
void ld_cb(Fl_Widget* o, void* v=0) {
	neuralNet.load("1.ini");
}

void sv_cb(Fl_Widget* o, void* v=0) {
	neuralNet.save("1.ini");
}


void s_cb(Fl_Widget* o, void* v = 0){
	Fl_Button* b = (Fl_Button*)o;
	int t = get_no[b];
	if (x[train_sum][t] == 1) { 
		b->label("");
		x[train_sum][t] = 0;
	}
	else {
		b->label("1");
		x[train_sum][t] = 1;
	}
	
	cout << x[train_sum][t]<<"  "<<t<<endl;
}



int main() {
	for (int i = 0; i < num_char; ++i) char_to_num[no_to_char[i]] = i;
	

	Fl_Double_Window win(1000, 800,"recognizer");
	int* val=new int(0);
	win.begin();
	Fl_Input *inpu = new Fl_Input(100, 10, 100, 30, "true value");
	Fl_Button *tra = new Fl_Button(10, 50, 100, 30, "train");
	Fl_Button *clr = new Fl_Button(210, 50, 100, 30, "clear");
	Fl_Button *reco = new Fl_Button(110, 50, 100, 30, "recognize");
	Fl_Button *ld = new Fl_Button(310, 50, 100, 30, "load");
	Fl_Button *sv = new Fl_Button(410, 50, 100, 30, "save");
	Fl_Button *traA = new Fl_Button(510, 50, 100, 30, "train all");
	
	for (int i = 0; i < level; ++i)
		for (int j = 0; j < level; ++j){
			for (int k = 0; k < 1000; ++k) x[k][i*level + j] = 0;
			ss[i][j] = new Fl_Button(200 + 20 * j, 200 + 20 * i, 20, 20, "");
			ss[i][j]->type(FL_TOGGLE_BUTTON);
			ss[i][j]->clear();
			ss[i][j]->label("");
			get_no[ss[i][j]] = i * level + j;
			
		}
	for (int i = 0; i < level; ++i)
		for (int j = 0; j < level; ++j){
			ss[i][j]->callback(s_cb, val);
		}


	tra->callback(train_cb, inpu);
	reco->callback(recog_cb);
	clr->callback(clr_cb, ss);
	ld->callback(ld_cb);
	sv->callback(sv_cb);

	win.end();
	win.show();
	return Fl::run();
}