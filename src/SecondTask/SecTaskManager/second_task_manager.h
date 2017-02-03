#pragma once

#ifndef SECOND_TASK_MANAGER
#define SECOND_TASK_MANAGER

#include"../LocalPosSolver/local_pos_solver.h"

#include<string>
#include<vector>

#include<tuple>


typedef std::tuple<std::string, std::string, int> Tuple;




template<typename T>
class SecondTaskManager
{
public:
	// Поэксперименитровать с const и & в конструкторе
	SecondTaskManager(const double T, std::string dotsFileName, std::string conditionsFileName);
	~SecondTaskManager();

	void CalculateLocalPositions();


private:

	void GetDotsDataFromFile(std::ifstream & in);

	// Time
	double TIn_;

	// First input file data
	std::string dotsFileName_;
	long int dotsNumber_;


	// Second input file data
	std::string conditionsFileName_;
	long int conditionsNumber_;

	std::vector< Tuple > tuples_;
	LocalPositionSolver<T>* localSoverPtr_;

};

#include"second_task_manager_impl.h"

#endif // !SECOND_TASK_MANAGER
