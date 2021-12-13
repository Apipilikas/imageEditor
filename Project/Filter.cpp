#include <iostream>
#include "Filter.h"


// Implamentation of Filter class
Filter::Filter() {
}

Filter::Filter(const Filter& fltr) {
}
//Implementation of FilterLinear class
FilterLinear::FilterLinear() {
}

FilterLinear::FilterLinear(Color a, Color c) {
	this->a = a;
	this->c = c;
}

FilterLinear::FilterLinear(const FilterLinear& fltr) {
	this->a = fltr.a;
	this->c = fltr.c;
}

void FilterLinear::setAC(Color a, Color c) {
	this->a = a;
	this->c = c;

}

Image FilterLinear::operator << (const Image& image) {
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

//Implementation of FilterGamma class
FilterGamma::FilterGamma() {
}

FilterGamma::FilterGamma(float c) {
	if (c >= 0.5f && c <= 2.0f) {
		this->c = c;
	}
	else {
		this->c = 0.5f;
	}
}

FilterGamma::FilterGamma(const FilterGamma& fltr) {
	this->c = fltr.c;
}

void FilterGamma::setGamma(float c) {
	this->c = c;
}

Image FilterGamma::operator << (const Image& image) {
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