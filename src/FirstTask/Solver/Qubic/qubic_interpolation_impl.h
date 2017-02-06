#pragma once

#ifndef QUBIC_INTERPOLATION_IMPL
#define QUBIC_INTERPOLATION_IMPL

#include"qubic_interpolation.h"

template<typename T>
QubicInterpolationSolver<T>::QubicInterpolationSolver() : InterpolationSolver() {}

template<typename T>
void QubicInterpolationSolver<T>::BuildInterpolation()
{
	// Prepare memory for result vector
	int size = inputPairs_.size();
	spline_.resize(size, QubicTuple<T>());

	for (int i = 0; i < size; ++i)
	{
		// Calculate a-coef value
		spline_.at(i).a = inputPairs_.at(i).value;

		// Set boundaries for each interval
		spline_.at(i).leftBoundary = inputPairs_.at(i).arg;
		spline_.at(i).rightBoundary = (i == inputPairs_.size() - 1) ? inputPairs_.at(i).arg + 1e-3 : inputPairs_.at(i + 1).arg;
	}

	// Vector store coefficients for Sweep line algorithm
	std::vector<double> alpha(size - 1);
	std::vector<double> beta(size - 1);

	double A, B, C, F, leftDelta, rightDelta, temp;

	// Direct  pass of Sweep line algorithm
	for (int i = 1; i < size - 1; ++i)
	{
		leftDelta = inputPairs_.at(i).arg - inputPairs_.at(i - 1).arg;
		rightDelta = inputPairs_.at(i + 1).arg - inputPairs_.at(i).arg;

		A = leftDelta;
		C = 2.0 * (leftDelta + rightDelta);
		B = rightDelta;
		F = 6.0 * ( (inputPairs_.at(i + 1).value - inputPairs_.at(i).value ) / rightDelta -
			( inputPairs_.at(i).value - inputPairs_.at(i - 1).value ) / leftDelta );

		temp = (A * alpha[i - 1] + C);

		alpha.at(i) = - B / temp;
		beta.at(i) = (F - A * beta.at(i - 1)) / temp;
	}

	// Calculate c-coef value for last interval
	spline_.at(size - 1).c = (F - A * beta.at(size - 2)) / (C + A * alpha.at(size - 2));

	// Backward pass of Sweep line algorithm c-coefs calculation
	for (int i = size - 2; i > 0; --i)
		spline_.at(i).c = alpha.at(i) * spline_.at(i + 1).c + beta.at(i);

	// Calculate all left coef value
	for (int i = size - 1; i > 0; --i)
	{
		double leftDelta = inputPairs_.at(i).arg - inputPairs_.at(i - 1).arg;

		spline_.at(i).d = (spline_.at(i).c - spline_.at(i - 1).c) / leftDelta;
		spline_.at(i).b = leftDelta * (2. * spline_.at(i).c + spline_.at(i - 1).c) / 6. + (inputPairs_.at(i).value - inputPairs_.at(i - 1).value) / leftDelta;
	}
}


template<typename T>
T QubicInterpolationSolver<T>::FindInterpolationValue(T const x)
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
inline T QubicInterpolationSolver<T>::BinSearch(const std::vector<QubicTuple<T>>& vec, int left, int right, T x) const
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
			QubicTuple<T> res = vec.at(middle);
			double dx = x - res.leftBoundary;
			return res.a + (res.b + (res.c / 2. + res.d * dx / 6.) * dx) * dx;
		}
	}
}

#endif // !QUBIC_INTERPOLATION_IMPL
