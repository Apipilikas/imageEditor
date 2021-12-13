#include <iostream>
#include "ppm/ppm.h"
#include "Project/array2d.h"
#include "Project/vec3.h"
#include "Project/imageio.h"
using namespace std;

#ifndef IMAGE_H
#define IMAGE_H

typedef math::Vec3<float> Color;

class Image : public math::Array2D<Color>, public image::ImageIO{

public:

	//Constructor
	Image() : Array2D() {
	}

	//Copy constructor call copy constructor of Array2D
	Image(const Image& img) : Array2D(img) {
	}

	//Destructor
	~Image() {
	}
	
	bool image::ImageIO::load(const std::string& filename, const std::string& format) {
		//checking if the file is .ppm format
		if (format.compare("ppm") == 0) {
			float* floatImg;
			int w, h;
			floatImg = image::ReadPPM(filename.c_str(), &w, &h);
			if (! floatImg) {
				return false;
			}
			Color* pixels = new Color[w * h];
			for (int ih = 0; ih < h; ih++) {
				for (int iw = 0; iw < w; iw++) {
					pixels[ih * w + iw] = Color(floatImg[ih * w * 3 + iw * 3],			//r
												floatImg[ih * w * 3 + iw * 3 + 1],		//g 
												floatImg[ih * w * 3 + iw * 3 + 2]);		//b 
				}
			}
			(*this).height = h;
			(*this).width = w;
			(*this).setData(pixels);
			
			delete[] floatImg;
			delete[] pixels;
			return true;
		}
		else {
			cerr << ">!< Error : The file you entered is not .ppm >!<" << endl;
			return false;
		}
		
	}

	bool image::ImageIO::save(const std::string& filename, const std::string& format) {
		if (format.compare("ppm") == 0) {
			float* floatImg = new float[width * height * 3];
			for (int ih = 0; ih < height; ih++) {
				for (int iw = 0; iw < width; iw++) {
					floatImg[ih * width * 3 + iw * 3] = buffer[ih * width + iw].r;
					floatImg[ih * width * 3 + iw * 3 + 1] = buffer[ih * width + iw].g;
					floatImg[ih * width * 3 + iw * 3 + 2] = buffer[ih * width + iw].b;
				}
			}
			bool flag = image::WritePPM(floatImg, width, height, filename.c_str());
			delete[] floatImg;
			return flag;
		}
		else {
			return false;
		}
	}
};
#endif // !IMAGE_H