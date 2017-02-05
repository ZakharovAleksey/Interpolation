#pragma once

#ifndef I_INTERPOLATION
#define I_INTERPOLATION

#include<vector>

template<typename T>
struct Pair;

// Interface for Interpolation class
template<typename T>
class iInterpolation
{
public:
	virtual ~iInterpolation() { }
	
	// Calculate interpolation spline
	virtual void BuildInterpolation() = 0;

	// Calculate ALL valuee (y) for ALL apropriate argument values (x) according to interpolation spline
	virtual std::vector<Pair<T>> FindAllInterpolationValues() = 0;
	// Calculate value (y) for apropriate argument value (x) according to interpolation spline
	virtual T FindInterpolationValue( T const x ) = 0;

};

#endif // !I_INTERPOLATION
