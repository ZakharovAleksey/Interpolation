#pragma once

#ifndef TASK_MANAGER
#define TASK_MANAGER

#include"..\Solver\Interpolation.h"

#include"../Solver/Linear/linear_interpolation.h"
#include"../Solver/Quadratic/quadratic_interpolation.h"
#include"../Solver/Qubic/qubic_interpolation.h"


#include<string>
#include<cstring>
#include<memory>

template<typename T>
class TaskManager
{
public:

	TaskManager(std::string fileName1, std::string fileName2, std::string outFileName);
	~TaskManager();

	// Implements solving procedure
	void Solve();


private:

	// Function allow user to choose interpolation order
	void ChooseInterpolationType();

	/// <summary>
	/// Function gets necessary data from appropriate file
	/// </summary>
	/// <param name="in"> Ifstream object for reading data from the file </param>
	/// <param name="fileNumber"> Number of input file (1 or 2) </param>
	/// <param name="fileName"> Name of input file </param>
	void GetDataFromFile(std::ifstream & in, const int fileId, std::string const & fileName);

	void WriteResultToFile(const std::vector<Pair<T>> & res) const;

	std::unique_ptr<InterpolationSolver<T>> solverPtr_;
	//InterpolationSolver<T>* solverPtr_;

	// First input file data
	std::string fileName1_;
	long int pointNumber1_;

	// Second input file data
	std::string fileName2_;
	long int pointNumber2_;

	std::string outFileName_;
};

#include"task_manager_impl.h"

#endif // !TASK_MANAGER
