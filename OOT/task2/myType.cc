#include <iostream>
#include "myType.h"
using namespace std;

template <typename T>
MyType<T>::MyType() {
}

template <typename T>
MyType<T>::MyType(T val) {
	value = val;
}

template <typename T>
MyType<T>::~MyType() {
}

template <typename T>
T MyType<T>::getValue() {
	return value;
}

template <typename T>
void MyType<T>::setValue(T val) {
	value = val;
}

template <typename T>
MyType<T> MyType<T>::operator+(MyType<T>& s) {
				T rslt = value + s.value;
				MyType<T> fei= MyType<T>(rslt);
				return fei;
}
			
template <typename T>
MyType<T> MyType<T>::operator-(MyType<T>& s) {
				T rslt = value - s.value;
				MyType<T> fei= MyType<T>(rslt);
				return fei;
}
			
