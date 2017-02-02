#pragma once

#ifndef INTERPOLATION
#define INTERPOLATION

#include"iInterpolation.h"

#include<vector>

template<typename T>
struct Pair
{
	T arg;
	T value;

	Pair() : arg(T()), value(T()) { }

	Pair(T point, T value) : arg(point), value(value) { }
};


template<typename T>
class InterpolationSolver : public iInterpolation<T>
{
public:
	InterpolationSolver();
	virtual ~InterpolationSolver();

	void SetInutPairs(const std::vector<Pair<T>> & inputPairs);
	void SetOutputPoints(const std::vector<T> & outputPoints);

	void DisplayInputData() const;

	void BuildInterpolation() override;
	void FindAllInterpolationValues() override;
	T FindInterpolationValue(T const x) override;

protected:
	std::vector<Pair<T>>  inputPairs_;
	std::vector<T>  outputPoints_;
};


#include"interpolation_impl.h"

#endif // !INTERPOLATION





