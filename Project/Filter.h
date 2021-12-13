#include <iostream>
#include "Image.h"


#ifndef FILTER_H
#define FILTER_H

typedef math::Vec3<float> Color;

//Implementation of Filter class
class Filter {

public:
	Filter() {}

	Filter(const Filter& fltr) {}

	virtual Image operator <<(const Image& image) = 0;

};

//Implementation of Filter Linear class
class FilterLinear : public Filter {

private:
	Color a;
	Color c;

public:
	FilterLinear() {
	}

	FilterLinear(Color a, Color c) {
		this->a = a;
		this->c = c;
	}

	FilterLinear(const FilterLinear& fltr) {
		this->a = fltr.a;
		this->c = fltr.c;
	}

	void setAC(Color a, Color c) {
		this->a = a;
		this->c = c;

	}

	Image operator << (const Image& image) {
		Color clr;
		Image Img(image);
		for (int h = 1; h <= image.getHeight(); h++) {
			for (int w = 1; w <= image.getWidth(); w++) {
				clr = a * Img(w, h) + c;
				clr = clr.clampToLowerBound(0.0f);
				clr = clr.clampToUpperBound(1.0f);
				Img(w, h) = clr;
			}
			
		}
		return Img;
	}

};

//Implementation of Filter Gamma class
class FilterGamma : public Filter {

private:
	float c;

public:
	FilterGamma() {
		this->c = 0.5f;
	}

	FilterGamma(float c) {
		if (c >= 0.5f && c <= 2.0f) {
			this->c = c;
		}
		else {
			this->c = 0.5f;
		}
	}

	FilterGamma(const FilterGamma& fltr) {
		this->c = fltr.c;
	}

	void setGamma(float c) {
		this->c = c;
	}

	Image operator << (const Image& image) {
		Color clr;
		Image Img(image);
		for (int h = 1; h <= image.getHeight(); h++) {
			for (int w = 1; w <= image.getWidth(); w++) {
				clr = Img(w, h);
				for (int i = 0; i < 2; i++) {
					clr[i] = pow(clr[i], c);
				}
				Img(w, h) = clr;
				
			}
		}
		return Img;
	}

};
#endif // !FILTER_H
