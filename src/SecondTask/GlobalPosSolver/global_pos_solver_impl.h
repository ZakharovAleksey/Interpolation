#pragma once

#ifndef GLOBAL_POS_SOLVER_IMPL
#define GLOBAL_POS_SOLVER_IMPL

#include"global_pos_solver.h"
#include <algorithm>

template<typename T>
GlobalPositionSolver<T>::GlobalPositionSolver()
{}

template<typename T>
GlobalPositionSolver<T>::~GlobalPositionSolver() {}

template<typename T>
inline void GlobalPositionSolver<T>::CalculateGlobalPosition(std::map<std::string, T> localPosition, std::vector<CondPair> conditions)
{
	//>>>>>>>>>>>>
	std::cout << "Hello\n";

	std::cout << "Local coordinates:\n";
	for (auto i : localPosition)
		std::cout << i.first << " -> " << i.second << std::endl;

	std::cout << "Conditions:\n";
	for (auto i : conditions)
		std::cout << i.first << " --- " << i.second << std::endl;

	//>>>>>>>>>>>

	std::map<std::string, T> globalPosition = localPosition;

	std::vector<std::string> dotsName;

	for (auto i : localPosition)
		dotsName.push_back(i.first);

	
	std::vector<std::string> leftCondition;
	std::vector<std::string> rightCondition;

	// Write conditions to vector
	for (auto i : conditions)
	{
		leftCondition.push_back(i.first);
		rightCondition.push_back(i.second);
	}

	while (!leftCondition.empty())
	{



		// Имена точке, которые мы не нашли в правой стороне (то есть у них нет зависимостей)
		std::vector<std::string> notFoundDots;

		// Тут мы составляем массив из тех точке которые не встретились в правой части
		for (auto dotName : dotsName)
		{
			if (std::find(rightCondition.begin(), rightCondition.end(), dotName) == rightCondition.end())
			{
				notFoundDots.push_back(dotName);
			}
		}

		std::cout << "Not found: \n";
		for (auto i : notFoundDots)
			std::cout << i << " ";
		std::cout << std::endl;

		std::cout << "Global position: \n";
		for (auto i : globalPosition)
			std::cout << i.first << " |-> " << i.second << std::endl;

		for (auto notFoundDot : notFoundDots)
		{
			for (int i = 0; i < leftCondition.size();)
			{
				if (leftCondition.at(i) == notFoundDot)
				{
					globalPosition.at(rightCondition.at(i)) += globalPosition.at(leftCondition.at(i));
					leftCondition.erase(leftCondition.begin() + i);
					rightCondition.erase(rightCondition.begin() + i);
				}
				else
					++i;
			}
			dotsName.erase(std::find(dotsName.begin(), dotsName.end(), notFoundDot));
		}
		notFoundDots.clear();

		std::cout << "AFTER\n";
		std::cout << "New Conditions:\n";
		for (int i = 0; i < leftCondition.size(); ++i)
		{
			std::cout << leftCondition.at(i) << " - >" << rightCondition.at(i) << std::endl;
		}

		std::cout << "Now dot left: ";
		for (auto i : dotsName)
			std::cout << i << " ";
		std::cout << std::endl;

		std::cout << "Global position: \n";
		for (auto i : globalPosition)
			std::cout << i.first << " |-> " << i.second << std::endl;


	}
	// Смотрим те вершины что не встерчаются в правой колонке, и потом обновляем все значения


}


#endif // !GLOBAL_POS_SOLVER_IMPL
