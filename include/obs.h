#pragma once

#include <functional>
#include <iostream>

#include "confUtils.h"




template <class T, class Field_t>
class WLoops{
	const GField<T>& field;
public:
	WLoops(const GField<T>& field): field(field) {}

	T calc_1x1_at( 
		size_t t,
		size_t x, 
		size_t y, 
		size_t z,
		const size_t mu, 
		const size_t nu) const
	{

		std::reference_wrapper<size_t> coord[] = {t, x, y, z};

		Field_t link(field.getFieldAt(t, x, y, z, mu));

		coord[mu]++;
		link *= Field_t(field.getFieldAt(t, x, y, z, nu));		
		coord[mu]--;
		
		coord[nu]++;
		link *= Field_t(field.getFieldAt(t, x, y, z, mu)).doHerm();		
		coord[nu]--;
		
		
		link *= Field_t(field.getFieldAt(t, x, y, z, nu)).doHerm();		

		return link.trace();
	}

};