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
SecondTaskManager<T>::SecondTaskManager(const double TIn, std::string dotsFileName, std::string conditionsFileName) :
	TIn_(TIn), dotsFileName_(dotsFileName), conditionsFileName_(conditionsFileName)
{
	localSoverPtr_ = new LocalPositionSolver<T>();
	globalSolverPtr_ = new GlobalPositionSolver<T>();

	std::ifstream in;

	GetDotsDataFromFile(in);
	GetConditionsFromFile(in);

}

template<typename T>
SecondTaskManager<T>::~SecondTaskManager() {}

template<typename T>
inline void SecondTaskManager<T>::CalculateLocalPositions()
{
	std::map<std::string, T> localCoordinates;
	localCoordinates = localSoverPtr_->CalculateLocalPositions(tuples_, TIn_);

	globalSolverPtr_->CalculateGlobalPosition(localCoordinates, pairs_);
}

template<typename T>
inline void SecondTaskManager<T>::GetDotsDataFromFile(std::ifstream & in)
{
	in.open(dotsFileName_ + ".txt");

	if (in.is_open())
	{
		// Store number of dots and check it on correctness
		in >> dotsNumber_;

		if (dotsNumber_ <= 0)
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

			/*for (auto i : tuples_)
				std::cout << std::get<0>(i) << " ||| " << std::get<1>(i) << " |||| " << std::get<2>(i) << std::endl;*/

			in.close();
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
	in.open(conditionsFileName_ + ".txt");

	if (in.is_open())
	{
		// Store number of dots and check it on correctness
		in >> dotsNumber_;

		if (dotsNumber_ <= 0)
		{
			in.close();

			std::string exceptionMessage = "Invalid number of the points in" + conditionsFileName_ + ".txt file!\n";
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

			/*for (auto i : pairs_)
				std::cout << i.first << " + " << i.second << std::endl;*/

			in.close();
		}
	}
	else
	{
		in.close();

		std::string exceptionMessage = "Could not open input file : " + conditionsFileName_ + ".txt!\n";
		throw exceptionMessage;
	}
}


#endif // !SECOND_TASK_MANAGER_IMPL
