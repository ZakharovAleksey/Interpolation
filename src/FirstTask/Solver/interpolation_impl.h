#pragma once

#ifndef INTERPOLATION_IMPL
#define INTERPOLATION_IMPL

#include "Interpolation.h"

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
	dotsForInterpolation_ = outputPoints;
}

template<typename T>
inline void InterpolationSolver<T>::DisplayInputData() const
{
	std::cout << "Input pairs: \n";
	for (auto curPair : inputPairs_)
		std::cout << curPair.arg << " " << curPair.value << std::endl;

	std::cout << "Output points: \n";
	for (auto curPoint : dotsForInterpolation_)
		std::cout << curPoint << std::endl;
}


template<typename T>
void InterpolationSolver<T>::BuildInterpolation() { }

template<typename T>
inline std::vector<Pair<T>> InterpolationSolver<T>::FindAllInterpolationValues() 
{
	std::vector<Pair<T>> result;
	Pair<T> curPair;

	for (auto x : dotsForInterpolation_)
	{
		curPair.arg = x;
		curPair.value = FindInterpolationValue(x);
		result.push_back(curPair);
	}

	return result;
}

template<typename T>
T InterpolationSolver<T>::FindInterpolationValue(T const x) { return T(); }

#endif // !INTERPOLATION_IMPL
