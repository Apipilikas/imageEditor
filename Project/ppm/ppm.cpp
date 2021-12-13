#include <iostream>
#include <fstream>
#include "ppm.h"

using namespace std;

namespace image
{
	float* ReadPPM(const char* filename, int* w, int* h) {

		ifstream iFile(filename, ios::in | ios::binary);

		if (! iFile.is_open()) {
			cout << ">!< Error : Could not open the file >!<" << endl;
			return 0;
		}
		else {
			string ppmFormat;
			int mav;
			iFile >> ppmFormat >> *w >> *h >> mav;
			//Checking if the PPM Format is P6 type
			if (ppmFormat.compare("P6")) {
				cout << ">!< Error : The PPM file is not P6 type >!<" << endl;
				return 0;
			}
			//Checking if maximum available value is 255
			if (mav != 255) {
				cout << ">!< Error : Maximum available value than can be stored is not 255 or width or height miss >!<" << endl;
				return 0;
			}


			int sizeOfImg = 3 * *w * *h;
			unsigned char* buffer = new unsigned char[sizeOfImg + 1];
			float* floatImg = new float[sizeOfImg];
			iFile.read((char*)buffer, sizeOfImg);

			for (int i = 0; i < sizeOfImg; i++) {
				floatImg[i] = (float)buffer[i + 1] / 255.0f;
			}
			delete[] buffer;
			return floatImg;
		}
	}
	
	bool WritePPM(const float* data, int w, int h, const char* filename) {

		ofstream oFile(filename, ios::out | ios::binary);

		if (! oFile.is_open()) {
			cout << ">!< Error : Could not write the file >!<" << endl;
			return false;
		}
		else {
			int sizeOfImg = 3 * w * h;
			unsigned char* bufferWriter = new unsigned char[sizeOfImg];
			for (int i = 0; i < sizeOfImg; i++) {
				bufferWriter[i] = data[i] * 255.0f;
			}
			oFile << "P6" << endl;
			oFile << w << endl;
			oFile << h << endl;
			oFile << "255" << "\r";
			oFile.write((char*)bufferWriter, sizeOfImg);
			delete[] bufferWriter;
			return true;
		}
	}
}
