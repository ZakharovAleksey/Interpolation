#pragma once

#ifndef QUADRATIC_INTERPOLLATION
#define QUADRATIC_INTERPOLLATION

#include"../Interpolation.h"

#include<vector>

template<typename T>
class QuadraticInterpolationSolver : public InterpolationSolver<T>
{
public:

	// Structure wich store information about current interval
	// Equation of parabola: y = ax^2 + bx + c
	template<typename T1>
	struct QuadraticTuple
	{
		T1 a;
		T1 b;
		T1 c;
		T1 leftBoundary;
		T1 rightBoundary;

		QuadraticTuple() : a(0), b(0), leftBoundary(0), rightBoundary(0) {}

		QuadraticTuple(T1 a, T1 b, T1 leftBoundary, T1 rightBoundary) : a(a), b(b), leftBoundary(leftBoundary), rightBoundary(rightBoundary) {}
	};

	QuadraticInterpolationSolver();
	~QuadraticInterpolationSolver() {}

	// Build interpolation coeffisients
	void BuildInterpolation() override;
	// Find interpolation values for all input argumnets
	void FindAllInterpolationValues() override;
	// Find interpolation value of input argumnet
	T FindInterpolationValue(T const x) override;

private:

	std::vector<QuadraticTuple<T>> spline_;
};

#include"quadratic_interpolation_impl.h"

#endif // !QUADRATIC_INTERPOLLATION
