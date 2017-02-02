#include "Interpolation.h"
#pragma once

#ifndef INTERPOLATION_IMPL
#define INTERPOLATION_IMPL

#include<iostream>

template<typename T>
InterpolationSolver<T>::InterpolationSolver() {}

template<typename T>
InterpolationSolver<T>::~InterpolationSolver() {}

template<typename T>
inline void InterpolationSolver<T>::SetInutPairs(const std::vector<Pair<T>>& inputPairs)
{
	inputPairs_ = inputPairs;
}

template<typename T>
inline void InterpolationSolver<T>::SetOutputPoints(const std::vector<T>& outputPoints)
{
	outputPoints_ = outputPoints;
}

template<typename T>
inline void InterpolationSolver<T>::DisplayInputData() const
{
	std::cout << "Input pairs: \n";
	for (auto curPair : inputPairs_)
		std::cout << curPair.arg << " " << curPair.value << std::endl;

	std::cout << "Output points: \n";
	for (auto curPoint : outputPoints_)
		std::cout << curPoint << std::endl;
}



template<typename T>
void InterpolationSolver<T>::BuildInterpolation() { }

template<typename T>
inline void InterpolationSolver<T>::FindAllInterpolationValues() { }

template<typename T>
T InterpolationSolver<T>::FindInterpolationValue(T const x) { return T(); }

#endif // !INTERPOLATION_IMPL
