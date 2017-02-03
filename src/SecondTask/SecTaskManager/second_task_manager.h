#pragma once

#ifndef SECOND_TASK_MANAGER
#define SECOND_TASK_MANAGER

#include"../LocalPosSolver/local_pos_solver.h"

#include<string>
#include<vector>

#include<tuple>


typedef std::tuple<std::string, std::string, int> Tuple;


// Class deals with second task and interuct with Solvers.
// All main algorithm consist from next steps:
// - Manager get data from first file (Tuples)
// - Manager send this data to LocalPositionSolver 
// - LocalPositionSolver calculates local positions of all dots and send them to Manager
// - Manager get data from second file (conditions on global dots)
// - Manager send this data to GlobalPositionSolver 
// - GlobalPositionSolver obtains global positions of all dots and send them to Manager
// - Manager write down this data to output file

template<typename T>
class SecondTaskManager
{
public:
	// Поэксперименитровать с const и & в конструкторе
	SecondTaskManager(const double T, std::string dotsFileName, std::string conditionsFileName);
	~SecondTaskManager();

	// Calculate local coordinates for all dots 
	// Tuple = (dotName(Id = 0), dotKeyPoints(Id = 1) interpolationOrder(Id = 2))
	void CalculateLocalPositions();


private:

	// Create vector of tuples ()
	void GetDotsDataFromFile(std::ifstream & in);

	// Time moment
	double TIn_;

	// First input file data
	std::string dotsFileName_;
	long int dotsNumber_;

	// Second input file data
	std::string conditionsFileName_;
	long int conditionsNumber_;

	// Store tuples from first file: 
	// Tuple = (dotName(Id = 0), dotKeyPoints(Id = 1) interpolationOrder(Id = 2))
	std::vector< Tuple > tuples_;

	// Pointer to local solver
	LocalPositionSolver<T>* localSoverPtr_;

};

#include"second_task_manager_impl.h"

#endif // !SECOND_TASK_MANAGER
