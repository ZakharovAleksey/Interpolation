#pragma once

#ifndef SECOND_TASK_MANAGER_IMPL
#define SECOND_TASK_MANAGER_IMPL

#include<fstream>
#include<iostream>
#include <sstream>
#include <iterator>
#include "second_task_manager.h"

#include<map>

template<typename T>
SecondTaskManager<T>::SecondTaskManager(const double TIn, const std::string dotsFileName, const std::string conditionsFileName) :
	TIn_(TIn), dotsFileName_(dotsFileName), conditionsFileName_(conditionsFileName)
{
	localSoverPtr_ = std::unique_ptr<LocalPositionSolver<T>>(new LocalPositionSolver<T>);
	globalSolverPtr_ = std::unique_ptr<GlobalPositionSolver<T>>(new GlobalPositionSolver<T>);

	std::ifstream in;

	GetDotsDataFromFile(in);
	GetConditionsFromFile(in);

}

template<typename T>
SecondTaskManager<T>::~SecondTaskManager() {}

template<typename T>
inline void SecondTaskManager<T>::CalculateGlobalPositions() 
{
	std::cout << "Calculation of global coordinates launched...\n";
	// Calculate local positions of all dots
	std::map<std::string, T> localPositions;
	localPositions = localSoverPtr_->CalculateLocalPositions(tuples_, TIn_);

	// Calculate global positions of all dots
	std::map<std::string, T> globalPositions;
	globalPositions = globalSolverPtr_->CalculateGlobalPosition(localPositions, pairs_);

	for (auto i : globalPositions)
		std::cout << i.first << " -> " << i.second << std::endl;

	// Write global positions of all dots in file
	WriteGlobalPositionToFile(globalPositions);
	std::cout << "Calculation of the global coordinate successfully completed\n";
}

template<typename T>
inline void SecondTaskManager<T>::GetDotsDataFromFile(std::ifstream & in)
{
	std::cout << "Uploading data from first input file... \n";
	in.open(dotsFileName_ + ".txt");

	if (in.is_open())
	{
		long int dotsNumber;
		// Store number of dots and check it on correctness
		in >> dotsNumber;

		if (dotsNumber <= 0)
		{
			in.close();

			std::string exceptionMessage = "Invalid number of the points in" + dotsFileName_ + ".txt file!\n";
			throw exceptionMessage;
		}
		else
		{
			// Read '\n' symbol left after dotsNumber_ reading
			in.get();

			Tuple curTuple;

			// Read file line by line and split each line in Triplet
			std::string curLine;
			while (std::getline(in, curLine))
			{
				// Splitting the line in to the 3 parts: dotName dotKeyPoints interpolationOrder
				std::istringstream buf(curLine);
				std::istream_iterator<std::string> beg(buf), end;

				std::vector<std::string> parts(beg, end);

				// Obtain interpolation order depending on last word in line
				int order = -1;
				if (parts.at(2) == "linear")
					order = 1;
				else if (parts.at(2) == "quadratic")
					order = 2;
				else if (parts.at(2) == "qubic")
					order = 3;

				// Make Tuple = (dotName(Id = 0), dotKeyPoints(Id = 1) interpolationOrder(Id = 2))
				curTuple = std::make_tuple(parts.at(0), parts.at(1), order);

				tuples_.push_back(curTuple);
			}

			in.close();
			std::cout << "Uploading the is was successful!\n";
		}
	}
	else
	{
		in.close();

		std::string exceptionMessage = "Could not open input file : " + dotsFileName_ + ".txt!\n";
		throw exceptionMessage;
	}
}


template<typename T>
inline void SecondTaskManager<T>::GetConditionsFromFile(std::ifstream & in)
{
	std::cout << "Uploading data from second input file... \n";
	in.open(conditionsFileName_ + ".txt");

	if (in.is_open())
	{
		long int conditionsNumber;
		// Store number of dots and check it on correctness
		in >> conditionsNumber;

		if (conditionsNumber <= 0)
		{
			in.close();

			std::string exceptionMessage = "Invalid number of conditions in" + conditionsFileName_ + ".txt file!\n";
			throw exceptionMessage;
		}
		else
		{
			// Read '\n' symbol left after dotsNumber_ reading
			in.get();

			// Read file line by line and split each line on pairs donName->dotName
			std::string curLine;
			std::string const split = "->";

			while (std::getline(in, curLine))
			{
				// Find spliting position
				size_t id = curLine.find(split);
				// Split line (-> length = 2 - thats why id + 2)
				pairs_.push_back(std::make_pair(curLine.substr(0, id), curLine.substr(id + 2)));
			}

			in.close();
			std::cout << "Uploading the is was successful!\n";
		}
	}
	else
	{
		in.close();

		std::string exceptionMessage = "Could not open input file : " + conditionsFileName_ + ".txt!\n";
		throw exceptionMessage;
	}
}

template<typename T>
inline void SecondTaskManager<T>::WriteGlobalPositionToFile(const std::map<std::string, T>& globalPositions) const
{
	std::ofstream out;
	out.open("SecondTaskFiles/globalPositions.txt");

	if (out.is_open())
	{
		out << globalPositions.size() << std::endl;

		for (auto pair : globalPositions)
			out << pair.first << " " << pair.second << std::endl;

		out.close();
	}
	else
	{
		out.close();

		std::string exceptionMessage = "Could not open input file : globalPositions.txt!\n";
		throw exceptionMessage;
	}
}


#endif // !SECOND_TASK_MANAGER_IMPL
