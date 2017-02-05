#pragma once

#ifndef LINEAR_INTERPOLLATION
#define LINEAR_INTERPOLLATION

#include"../Interpolation.h"

#include<vector>

// Linear interpolaation solver
template<typename T>
class LinearInterpolationSolver : public InterpolationSolver<T>
{
public:

	// Structure which store information about current spline interval
	// Equation: y = ax + b
	template<typename T1>
	struct LinearTuple
	{
		double a;
		double b;
		T1 leftBoundary;
		T1 rightBoundary;

		LinearTuple() : a(0), b(0), leftBoundary(0), rightBoundary(0) {}

		LinearTuple(T1 a, T1 b, T1 leftBoundary, T1 rightBoundary) : a(a), b(b), leftBoundary(leftBoundary), rightBoundary(rightBoundary) {}
	};

	LinearInterpolationSolver();
	~LinearInterpolationSolver() {}

	void BuildInterpolation() override;
	T FindInterpolationValue(T const x) override;

private:
	std::vector<LinearTuple<T>> spline_;
};

#include"linear_interpolation_impl.h"

#endif // !LINEAR_INTERPOLLATION
