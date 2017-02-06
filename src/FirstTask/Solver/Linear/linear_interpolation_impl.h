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
	
	if (spline_.at(0).leftBoundary > x || spline_.at(spline_.size() - 1).rightBoundary < x)
	{
		std::cout << " X = " << x << " is not in interval! \n";
		return T();
	}
	else
		return  BinSearch(spline_, 0, spline_.size(), x);
}

template<typename T>
inline T LinearInterpolationSolver<T>::BinSearch(const std::vector<LinearTuple<T>>& vec, int left, int right, T x) const
{
	int middle = 0;

	while (left <= right)
	{
		middle = (left + right) / 2;

		if (vec.at(middle).leftBoundary > x)
			right = middle;
		else if (vec.at(middle).rightBoundary < x)
			left = middle;
		else
		{
			LinearTuple<T> lol = vec.at(middle);
			return lol.a * x + lol.b;
		}
	}
}

#endif // !LINEAR_INTERPOLATION_IMPL
