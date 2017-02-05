#pragma once

#ifndef LINEAR_INTERPOLATION_IMPL
#define LINEAR_INTERPOLATION_IMPL

#include"linear_interpolation.h"

template<typename T>
LinearInterpolationSolver<T>::LinearInterpolationSolver() : InterpolationSolver() {}

template<typename T>
void LinearInterpolationSolver<T>::BuildInterpolation() 
{
	LinearTuple<T> curTuple;

	for (int i = 0; i < inputPairs_.size() - 1; ++i)
	{
		// Find a-coef and b-coef
		curTuple.a = (inputPairs_.at(i + 1).value - inputPairs_.at(i).value) / (inputPairs_.at(i + 1).arg - inputPairs_.at(i).arg);
		curTuple.b = inputPairs_.at(i).value - curTuple.a * inputPairs_.at(i).arg;

		// Obtain boundary of interval
		curTuple.leftBoundary = inputPairs_.at(i).arg;
		curTuple.rightBoundary = inputPairs_.at(i + 1).arg;

		spline_.push_back(curTuple);
	}

}

template<typename T>
T LinearInterpolationSolver<T>::FindInterpolationValue(T const x) 
{
	for (auto i : spline_)
	{
		// If the current x is belongs to one of intervals return interpolation value
		if (i.leftBoundary <= x && i.rightBoundary >= x)
		{
			return i.a * x + i.b;
		}
	}

	std::cout << " X = " << x << " is not in interval! \n";

	return T(); 
}

#endif // !LINEAR_INTERPOLATION_IMPL
