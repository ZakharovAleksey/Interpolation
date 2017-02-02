#pragma once

#ifndef TASK_MANAGER
#define TASK_MANAGER

#include"..\Solver\Interpolation.h"
#include"../Solver/Linear/linear_interpolation.h"
#include"../Solver/Quadratic/quadratic_interpolation.h"

#include<string>
#include<cstring>


template<typename T>
class TaskManager
{
public:
	TaskManager(std::string fileName1, std::string fileName2);
	~TaskManager();

	void Solve();

private:

	/// <summary>
	/// Function gets necessary data from appropriate file
	/// </summary>
	/// <param name="in"> ifstream </param>
	/// <param name="fileNumber"> Number of input file (1 or 2) </param>
	/// <param name="fileName"> Name of input file </param>
	void GetDataFromFile(std::ifstream & in, const int fileId, std::string const & fileName);

	InterpolationSolver<T>* solverPtr_;


	std::string fileName1_;
	long int pointNumber1_;
	std::string fileName2_;
	long int pointNumber2_;
};

#include"task_manager_impl.h"

#endif // !TASK_MANAGER
