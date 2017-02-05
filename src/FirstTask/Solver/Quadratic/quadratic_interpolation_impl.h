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
	for (auto i : spline_)
	{
		// If the current x is belongs to one of intervals return interpolation value
		if (i.leftBoundary <= x && i.rightBoundary >= x)
		{
			return i.a * x * x + i.b * x + i.c;
		}
	}

	std::cout << " X = " << x << " is not in interval!\n";

	return T();
}

#endif // !QUADRATIC_INTERPOLATION_IMPL
