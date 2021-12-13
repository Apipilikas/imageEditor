#ifndef _ARRAY2D_HPP
#define _ARRA2D_HPP
#include <vector>
#include "array2d.h"

namespace math
{

	template <typename T> const unsigned int Array2D<T>::getWidth() const {
		return width;
	}

	template <typename T> const unsigned int Array2D<T>::getHeight() const {
		return height;
	}
	// internal data pointer = pointer to internal array buffer --> Array2D
	//data_ptr is a pointer for Array2D array
	// returns an array of vector's data
	template <typename T> T* Array2D<T>::getRawDataPtr() {
		T* data_ptr = buffer.data();
		return data_ptr;
	}
	/* external raw buffer = float array --> data_ptr
	   internal array buffer = Array2
	*/
	template <typename T> void Array2D<T>::setData(const T* const& data_ptr) {
		buffer.resize(width * height);
		for (int i = 0; i < width * height; i++)
			buffer[i] = data_ptr[i];
	}
	//(x, y)
	// x = width
	// y = height
	// y * width + x 
	template <typename T> T& Array2D<T>::operator () (unsigned int x, unsigned int y) {
		return buffer[width * (y - 1) + x - 1];
	}

	//Constructor
	template <typename T> Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) {
		(*this).width = width;
		(*this).height = height;
		(*this).buffer.reserve(width * height);
		for (int i = 0; i < width * height; i++) {
			(*this).buffer.push_back(data_ptr[i]);
		}
	}

	//Copy constructor
	template <typename T>  Array2D<T>::Array2D(const Array2D& src) {
		width = src.width;
		height = src.height;
		buffer = src.buffer;
	}

	//Destructor
	template <typename T> Array2D<T>::~Array2D() {
		buffer.~vector<T>();
	}

	template <typename T> Array2D<T>& Array2D<T>::operator = (const Array2D& right) {
		(*this).width = right.width;
		(*this).height = right.height;
		(*this).buffer = right.buffer;
		return *this;
	}
}

#endif // !_ARRAY2D_HPP
