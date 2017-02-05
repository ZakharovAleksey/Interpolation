#pragma once

#ifndef SECOND_TASK_MANAGER
#define SECOND_TASK_MANAGER

#include"../LocalPosSolver/local_pos_solver.h"
#include"../GlobalPosSolver/global_pos_solver.h"

#include<memory>
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
	SecondTaskManager(const double T, const std::string dotsFileName, const std::string conditionsFileName);
	~SecondTaskManager();

	// Calculate Global positions of all dots
	void CalculateGlobalPositions();

private:
	// Get all data about each dot from first input file
	void GetDotsDataFromFile(std::ifstream & in);

	// Get all dots conditions from second input file
	void GetConditionsFromFile(std::ifstream & in);

	// Write calculated global positions of all dots in file
	void WriteGlobalPositionToFile(const std::map<std::string, T> & globalPositions) const;


	// Time moment
	double TIn_;

	// First input file data
	std::string dotsFileName_;

	// Second input file data
	std::string conditionsFileName_;

	// Store tuples from first file: 
	// Tuple = (dotName(Id = 0), dotKeyPoints(Id = 1) interpolationOrder(Id = 2))
	std::vector<Tuple> tuples_;

	// Store condition pair from second input file:
	// Pair = (leftDot(Id = 0), RightDot(Id = 1))
	typedef std::pair<std::string, std::string> PointsNamePair;
	std::vector<PointsNamePair> pairs_;
	
	// Pointer to local solver
	std::unique_ptr<LocalPositionSolver<T>> localSoverPtr_;

	//Pointer to global solver
	std::unique_ptr<GlobalPositionSolver<T>> globalSolverPtr_;
};

#include"second_task_manager_impl.h"

#endif // !SECOND_TASK_MANAGER
