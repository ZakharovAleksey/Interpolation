#pragma once

#ifndef GLOBAL_POS_SOLVER_IMPL
#define GLOBAL_POS_SOLVER_IMPL

#include"global_pos_solver.h"
#include <algorithm>

template<typename T>
GlobalPositionSolver<T>::GlobalPositionSolver() {}

template<typename T>
GlobalPositionSolver<T>::~GlobalPositionSolver() {}

template<typename T>
inline std::map<std::string, T> GlobalPositionSolver<T>::CalculateGlobalPosition( const std::map<std::string, T> & localPosition, const std::vector<CondPair> & conditions) const
{
	// Stores global position of all dots
	std::map<std::string, T> globalPosition = localPosition;

	// Stores dots names
	std::vector<std::string> dotsName;
	for (auto i : localPosition)
		dotsName.push_back(i.first);

	// Stores dots names in left and right parts of 
	// conditions. In file: leftCondition -> rightCondition (A->B)
	std::vector<std::string> leftCondition;
	std::vector<std::string> rightCondition;

	// Fill conditions
	for (auto i : conditions)
	{
		leftCondition.push_back(i.first);
		rightCondition.push_back(i.second);
	}

	// Loop until all conditions are used
	while (!leftCondition.empty())
	{
		// Dots name which we did not find in right side of the conditions
		std::vector<std::string> notFoundDots;
		for (auto dotName : dotsName)
		{
			// Look via the right part of conditions
			if (std::find(rightCondition.begin(), rightCondition.end(), dotName) == rightCondition.end())
				notFoundDots.push_back(dotName);
		}

		for (auto notFoundDot : notFoundDots)
		{
			for (int i = 0; i < leftCondition.size();)
			{
				// Update global position of right dot depending on the left dot global position
				if (leftCondition.at(i) == notFoundDot)
				{
					globalPosition.at(rightCondition.at(i)) += globalPosition.at(leftCondition.at(i));
					//  Remove conditions which has been used
					leftCondition.erase(leftCondition.begin() + i);
					rightCondition.erase(rightCondition.begin() + i);
				}
				else
					++i;
			}
			// Remove dots which has been used
			dotsName.erase(std::find(dotsName.begin(), dotsName.end(), notFoundDot));
		}

		notFoundDots.clear();
	}

	return globalPosition;
}


#endif // !GLOBAL_POS_SOLVER_IMPL
