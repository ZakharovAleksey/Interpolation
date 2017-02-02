#pragma once

#ifndef INTERPOLATION
#define INTERPOLATION

#include"iInterpolation.h"

#include<vector>

// Structure wich store pair:
// - agr (argument or x-coordinate of the point)
// - value (value or y = f(x) of this point)
template<typename T>
struct Pair
{
	T arg;
	T value;

	Pair() : arg(T()), value(T()) { }

	Pair(T point, T value) : arg(point), value(value) { }
};

// Comparator for further std::sort procedure
template<typename T>
bool PairComparator(const Pair<T> & left, const Pair<T> & right)
{
	return (left.arg < right.arg) ? true : false;
}


// Parent for all InterpolationSolver classes
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

	std::vector<Pair<T>> FindAllInterpolationValues() override;

	T FindInterpolationValue(T const x) override;

protected:
	std::vector<Pair<T>>  inputPairs_;
	std::vector<T>  outputPoints_;
};


#include"interpolation_impl.h"

#endif // !INTERPOLATION