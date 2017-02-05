#pragma once

#ifndef GLOBAL_POS_SOLVER
#define GLOBAL_POS_SOLVER

#include<vector>
#include<string>
#include<map>

// Class calculate global position of all dots
// depending on the local positions and their conditions
template<typename T>
class GlobalPositionSolver
{
	typedef std::pair<std::string, T> PosPair;
	typedef std::pair<std::string, std::string> CondPair;

public:
	GlobalPositionSolver();
	~GlobalPositionSolver();

	std::map<std::string, T> CalculateGlobalPosition(const std::map<std::string, T> & localPosition, const std::vector<CondPair> & conditions) const;
};


#include"global_pos_solver_impl.h"

#endif // !GLOBAL_POS_SOLVER
