#include "quadratic_interpolation.h"
#pragma once

#ifndef QUADRATIC_INTERPOLATION_IMPL
#define QUADRATIC_INTERPOLATION_IMPL

template<typename T>
QuadraticInterpolationSolver<T>::QuadraticInterpolationSolver() : InterpolationSolver() {}

template<typename T>
void QuadraticInterpolationSolver<T>::BuildInterpolation()
{
	QuadraticTuple<T> curTuple;

	for (int i = 1; i < inputPairs_.size() - 1; i+=2)
	{
		// Obtain a-coef, b-coef, c-coef
		curTuple.a =
			(inputPairs_.at(i + 1).value - inputPairs_.at(i - 1).value) /
			(inputPairs_.at(i + 1).arg - inputPairs_.at(i - 1).arg) /
			(inputPairs_.at(i + 1).arg - inputPairs_.at(i).arg)
			-
			(inputPairs_.at(i).value - inputPairs_.at(i - 1).value) /
			(inputPairs_.at(i).arg - inputPairs_.at(i - 1).arg) /
			(inputPairs_.at(i + 1).arg - inputPairs_.at(i).arg);

		curTuple.b =
			(inputPairs_.at(i).value - inputPairs_.at(i - 1).value) /
			(inputPairs_.at(i).arg - inputPairs_.at(i - 1).arg)
			-
			curTuple.a * (inputPairs_.at(i).arg + inputPairs_.at(i - 1).arg);

		curTuple.c =
			inputPairs_.at(i - 1).value -
			curTuple.b * inputPairs_.at(i - 1).arg -
			curTuple.a * inputPairs_.at(i - 1).arg * inputPairs_.at(i - 1).arg;

		curTuple.leftBoundary = inputPairs_.at(i - 1).arg;
		curTuple.rightBoundary = inputPairs_.at(i + 1).arg;

		spline_.push_back(curTuple);
	}

}

template<typename T>
T QuadraticInterpolationSolver<T>::FindInterpolationValue(T const x)
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
inline T QuadraticInterpolationSolver<T>::BinSearch(const std::vector<QuadraticTuple<T>>& vec, int left, int right, T x) const
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
			QuadraticTuple<T> res = vec.at(middle);
			return res.a * x * x + res.b * x + res.c;
		}
	}
}

#endif // !QUADRATIC_INTERPOLATION_IMPL
