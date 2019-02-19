#pragma once


#include <complex>


template <class T>
class SU2_t{
	// su2 matrix:
	// 	(a   b)
	// 	(-b* a*)
	std::complex<T> a, b;


public:
	SU2_t(const T* ptr): 
		a(ptr[0], ptr[1]), b(ptr[2], ptr[3])
	{}

	SU2_t& operator*=(const SU2_t& other)
	{
		const auto aOld(a);

		a *= other.a;
		a -= b*std::conj(other.b);

		b *= std::conj(other.a);
		b += aOld*other.b;
		return *this;
	}

	T trace(){
		return std::real(a) * 2.0;
	}

	SU2_t& doHerm(){
		a = std::conj(a);
		b = -b;

		return *this;
	}



};