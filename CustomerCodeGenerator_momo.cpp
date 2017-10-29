#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<time.h>
#define maxNum 50000
using namespace std;
int n; 
int h;
int customer[maxNum];
void Confinguration() {
	ifstream input;
	ifstream dbInput;
	input.open("Configuration.txt");
	dbInput.open("DB.txt");
	string k;

	if (input.is_open() == false || dbInput.is_open() == false) {
		cout << "Please check configuration.txt" << endl;
		cout << "Program will be shut down" << endl;
		exit(10);
	}
	while (!input.eof()) {
		input >> k;
		if (k == "Maximum") {
			input >> n;
			if (n > maxNum - 1) {
				cout << "Program can't get that data, because too heavier" << endl;
				cout << "Overflow : " << n << endl;
				cout << "Shutdown" << endl; exit(10);
			}
		}
		if (k == "hash") {
			input >> h;
		}
	}
	int i = 0;
	while (!dbInput.eof()) {
		if (i > maxNum - 1) {
			cout << "Data is too many to put in program" << endl;
		}
		else {
			dbInput >> customer[i++];
		}
	}
	n = i;
	input.close();
	dbInput.close();
}
bool isdata(int k) {
	int i;
	for (i = 0; i < n; i++) {
		if (k == customer[i]) return true;
	}
	return false;
}
int pow(int n, int m) {
	int k = n;
	if (m == 0) {
		return 1;
	}
	for (int i = 1; i < m; i++) {
		k *= 10;
	}
	return k;
}
int randomGenerate() {
	int m = 0;
	int p; int x;
	for (int i = 0; i < 8; i++) {
		p = pow(10, i);
		x = rand() % 10;
		m += p*x;
	}
	return m;
}
int main() {
	Confinguration();
	cout << "N : " << n << endl;
	if (h) {
		srand(h);
	}
	else {
		srand(time(NULL));
	}
	ofstream output;
	output.open("DB.txt", fstream::out | fstream::app);
	while (1) {
		int m;
		m = randomGenerate();
		if (!isdata(m)) {
			output << endl;
			output << m;
			cout << "Random data :: " << m << " :: is updated!" << endl;
			output.close();
			exit(10);
		}
	}
	return false;
}
