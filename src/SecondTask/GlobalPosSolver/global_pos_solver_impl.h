#pragma once

#ifndef GLOBAL_POS_SOLVER_IMPL
#define GLOBAL_POS_SOLVER_IMPL

#include"global_pos_solver.h"

template<typename T>
GlobalPositionSolver<T>::GlobalPositionSolver()
{}

template<typename T>
GlobalPositionSolver<T>::~GlobalPositionSolver() {}

template<typename T>
inline void GlobalPositionSolver<T>::CalculateGlobalPosition(std::map<std::string, T> localPosition, std::vector<CondPair> conditions)
{
	std::cout << "Hello\n";

	std::cout << "Local coordinates:\n";
	for (auto i : localPosition)
		std::cout << i.first << " -> " << i.second << std::endl;

	std::cout << "Conditions:\n";
	for (auto i : conditions)
		std::cout << i.first << " --- " << i.second << std::endl;

}


#endif // !GLOBAL_POS_SOLVER_IMPL
