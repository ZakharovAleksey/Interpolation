#pragma once

#ifndef QUBIC_INTERPOLLATION
#define QUBIC_INTERPOLLATION

#include"../Interpolation.h"

#include<vector>

template<typename T>
class QubicInterpolationSolver : public InterpolationSolver<T>
{
public:

	// Structure wich store information about current spline interval
	// Equation: y = a + b (x - x0) + c (x - x0)^2 + d (x - x0)^3
	template<typename T1>
	struct QubicTuple
	{
		double a;
		double b;
		double c;
		double d;
		T1 leftBoundary;
		T1 rightBoundary;

		QubicTuple() : a(0), b(0), c(0), d(0), leftBoundary(0), rightBoundary(0) {}

		QubicTuple(T1 a, T1 b, T1 c, T1 d, T1 leftBoundary, T1 rightBoundary) : a(a), b(b), c(c), d(d), leftBoundary(leftBoundary), rightBoundary(rightBoundary) {}
	};

	QubicInterpolationSolver();
	~QubicInterpolationSolver() {}

	void BuildInterpolation() override;
	T FindInterpolationValue(T const x) override;

private:
	std::vector<QubicTuple<T>> spline_;
};

#include"qubic_interpolation_impl.h"

#endif // !QUBIC_INTERPOLLATION
