#pragma once

#ifndef GLOBAL_POS_SOLVER
#define GLOBAL_POS_SOLVER

#include<vector>
#include<string>
#include<map>

template<typename T>
class GlobalPositionSolver
{
	typedef std::pair<std::string, T> PosPair;
	typedef std::pair<std::string, std::string> CondPair;

public:
	GlobalPositionSolver();
	~GlobalPositionSolver();

	void CalculateGlobalPosition(std::map<std::string, T> localPosition, std::vector<CondPair> conditions);

private:

	std::vector<PosPair> localPosition_;
	std::vector<CondPair> conditions_;
};


#include"global_pos_solver_impl.h"

#endif // !GLOBAL_POS_SOLVER
