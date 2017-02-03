#pragma once

#ifndef TASK_MANAGER_IMPL
#define TASK_MANAGER_IMPL


#include<fstream>
#include<vector>
#include <algorithm> 
#include<iostream>
#include "task_manager.h"

enum class InterpolationType
{
	Linear = 1,
	Quadratic = 2,
	Qubic = 3
};

template<typename T>
TaskManager<T>::TaskManager(std::string fileName1, std::string fileName2, std::string outFileName) : fileName1_(fileName1), fileName2_(fileName2), outFileName_(outFileName)
{
	ChooseInterpolationType();

	pointNumber1_ = -1;
	pointNumber2_ = -1;

	std::ifstream in;
	std::cout << "The data is loading...\n";

	GetDataFromFile(in, 1, fileName1_);
	GetDataFromFile(in, 2, fileName2_);

	std::cout << "The data is ready for interpolation procedure.\n";
	//solverPtr_->DisplayInputData();
}

template<typename T>
TaskManager<T>::~TaskManager() {}

template<typename T>
inline void TaskManager<T>::Solve()
{
	solverPtr_->BuildInterpolation();
	std::vector<Pair<T>> result = solverPtr_->FindAllInterpolationValues();

	std::cout << "Ñalculation finished successfully!\n";

	WriteResultToFile(result);
}

template<typename T>
inline void TaskManager<T>::ChooseInterpolationType()
{
	std::cout << "Choose interpolation type and input apropriate number:\n "
		<< " 1 - Linear interpolation (first order).\n "
		<< " 2 - Quadratic interpolation (secon order).\n "
		<< " 3 - Cubic interpolation(third order). \n";
	std::cout << "Your input: ";

	int interpolOrder = -1;
	bool isCorrectInput = false;

	// While user input is incorrect ask him to input valid interpolation type
	while (!isCorrectInput)
	{
		std::cin >> interpolOrder;

		// If user input is not a number
		if (!std::cin)
		{
			// Clear all user input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Wrong input! Please input 1(Linear) 2(Quadratic) or 3 (Qubic) interpolation.\nYour input:  ";
			continue;
		}

		switch (interpolOrder)
		{
		case int(InterpolationType::Linear) :
			solverPtr_ = new LinearInterpolationSolver<T>();
			isCorrectInput = true;
			break;
		case int(InterpolationType::Quadratic) :
			solverPtr_ = new QuadraticInterpolationSolver<T>();
			isCorrectInput = true;
			break;
		case int(InterpolationType::Qubic) :
			solverPtr_ = new QubicInterpolationSolver<T>();
			isCorrectInput = true;
			break;
		default:
			std::cout << "Wrong input! Please input 1(Linear) 2(Quadratic) or 3 (Qubic) interpolation.\nYour input:  ";
			break;
		}
	}
}

template<typename T>
inline void TaskManager<T>::GetDataFromFile(std::ifstream & in, const int fileId, std::string const & fileName)
{
	in.open(fileName + ".txt");

	if (in.is_open())
	{
		// Read number of points in the file
		in >> pointNumber1_;

		// Check on the correct input size
		if (pointNumber1_ <= 0)
		{
			in.close();

			std::string exceptionMessage = "File : " + fileName + ".txt is empty.";
			throw exceptionMessage;
		}
		else
		{
			// If first file - read pairs : (arg, value) or (x, y =f(x))
			if (fileId == 1)
			{
				std::vector<Pair<T>> vectorOfPairs;
				Pair<T> curPair;

				while (in.good())
				{
					in >> curPair.arg >> curPair.value;
					vectorOfPairs.push_back(curPair);
				}

				// Input data could be in wrong order, so we sort the data before future usage
				std::sort(vectorOfPairs.begin(), vectorOfPairs.end(), PairComparator<T>);

				solverPtr_->SetInutPairs(vectorOfPairs);
			}
			// If second file -  read args only or (x)
			else if (fileId == 2)
			{
				std::vector<T> pointsVector;
				T curPoint;

				while (in.good())
				{
					in >> curPoint;
					pointsVector.push_back(curPoint);
				}
				solverPtr_->SetOutputPoints(pointsVector);
			}
		}

		in.close();
	}
	else
	{
		std::string exceptionMessage = "Could not open input file : " + fileName + ".txt";
		throw exceptionMessage;
	}
}

template<typename T>
inline void TaskManager<T>::WriteResultToFile(const std::vector<Pair<T>> & res) const
{
	std::ofstream out;
	out.open(outFileName_ + ".txt");

	if (out.is_open())
	{
		// Write number of points and result data in format : x _ y = f(x)
		out << res.size() << std::endl;
		for (auto i : res)
			out << i.arg << " " << i.value << std::endl;

		out.close();
	}
	else
	{
		out.close();

		std::string exceptionMessage = "Could not open output file : " + outFileName_ + ".txt";
		throw exceptionMessage;
	}
}

#endif // !TASK_MANAGER_IMPL