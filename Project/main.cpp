//EVANGELOS PIPILIKAS | 3180157
// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "Filter.h"
using namespace std;

int main() {

	cout << "> filter ";
	string input;
	getline(cin, input);
	if (input.empty()) {
		cout << ">!< Error : Input is empty >!<";
		return 0;
	}
	//Finds the filename at the end of input
	int ln = input.length();
	while (ln >= 0 && input[ln] != ' ') {
		ln--;
	}
	string filename = input.substr(ln + 1);
	int d = filename.length() - 3;
	if (d < 0) {
		cerr << ">!< Error : You entered wrong filename >!<";
		return 0;
	}
	//Save ppm format
	string ppmFormat = filename.substr(filename.length() - 3);

	float acRGB[6];
	float gamma;
	int i = 0;
	Image Img;
	FilterLinear fl;
	FilterGamma fg;
	bool flag = false;
	if (!Img.load(filename, ppmFormat)) {
		return 0;
	}
	while (i < ln) {
		flag = true;
		
		if (input.substr(i,2).compare("-f") != 0) {
			cerr << ">!< Error : You entered wrong input >!<" << endl;
			flag = false;
			break;
		}
		else {
			i += 3;
		}
		if (input.substr(i, 6).compare("linear") == 0) {
			i += 7;
			try {
				for (int j = 0; j < 6; j++) {
					int s = i;
					while (input[s] != ' ') {
						s++;
					}
					acRGB[j] = stof(input.substr(i, s - i));
					i = s + 1;
				}
			}
			catch (logic_error) {
				cerr << ">!< Error : You entered wrong parameters in filter Linear >!<" << endl;
				flag = false;
				break;
			}
			Color a(acRGB[0], acRGB[1], acRGB[2]);
			Color c(acRGB[3], acRGB[4], acRGB[5]);
			fl.setAC(a, c);
			Img = fl << Img;
			
		}
		else if (input.substr(i, 5).compare("gamma") == 0) {
			i += 6;
			int s = i;
			while (input[s] != ' ') {
				s++;
			}
			try {
				gamma = stof(input.substr(i, s - i));
			}
			catch (logic_error) {
				cerr << ">!< Error : You entered wrong parameters in filter Gamma >!<" << endl;
				flag = false;
				break;
			}
			fg.setGamma(gamma);
			Img = fg << Img;
			i = s + 1;
		}
		else {
			cerr << ">!< Error : You entered wrong filter >!<" << endl;
			return 0;
		}
	}
	if (flag) {
		if (Img.save("filtered_" + filename, ppmFormat)) {
			cout << "> Image saved succesfully ! <" << endl;
		}
	}
	return 0;
}
