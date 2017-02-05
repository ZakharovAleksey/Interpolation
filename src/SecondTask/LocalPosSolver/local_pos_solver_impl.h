#include "local_pos_solver.h"
#pragma once

#ifndef LOCAL_POS_SOLVER_IMPL
#define LOCAL_POS_SOLVER_IMPL

template<typename T>
LocalPositionSolver<T>::LocalPositionSolver() : solverPtr_(nullptr) {}

template<typename T>
LocalPositionSolver<T>::~LocalPositionSolver() {}

template<typename T>
inline std::map<std::string, T> LocalPositionSolver<T>::CalculateLocalPositions(const std::vector<Tuple>& tuples, const double TIn)
{
	std::ifstream in;

	std::vector<Pair<T>> dotPosition;
	// Store pair: dot name and it's local position
	std::map<std::string, T> dotPosMap;

	// Loop by all tuples
	for (auto curTuple : tuples)
	{
		// Choose apropriate interpolation solver depending on dot interpolation order
		switch (std::get<2>(curTuple))
		{
		case 1:
			solverPtr_ = std::unique_ptr<LinearInterpolationSolver<T>>(new LinearInterpolationSolver<T>);
			break;
		case 2:
			solverPtr_ = std::unique_ptr<QuadraticInterpolationSolver<T>>(new QuadraticInterpolationSolver<T>);
			break;
		case 3:
			solverPtr_ = std::unique_ptr<QubicInterpolationSolver<T>>(new QubicInterpolationSolver<T>);
			break;
		default:
			std::cout << "Error! Wrong input interpolation order! Could not create apropriate solver!\n";
			break;
		}

		// Load time evolution of current dot form apropriate file
		// and build interpolation of choosen order
		dotPosition = GetDotTimeEvolution(in, std::get<1>(curTuple));
		solverPtr_->SetInutPairs(dotPosition);
		solverPtr_->BuildInterpolation();

		dotPosMap.insert(std::pair<std::string, T>(std::get<0>(curTuple), solverPtr_->FindInterpolationValue(TIn)));
	}

	return dotPosMap;
}

template<typename T>
inline std::vector<Pair<T>> LocalPositionSolver<T>::GetDotTimeEvolution(std::ifstream & in, std::string const & fileName)
{
	in.open("SecondTaskFiles/" + fileName);
	
	if (in.is_open())
	{
		
		// Read number of points in the file
		int dotsNumber; in >> dotsNumber;
	
		// Check on the correct input size
		if (dotsNumber <= 0)
		{
			in.close();
	
			std::string exceptionMessage = "File : " + fileName + ".txt is empty.";
			throw exceptionMessage;
		}
		else
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

			in.close();
			return vectorOfPairs;
		}
	}
	else
	{
		in.close();

		std::string exceptionMessage = "Could not open input file : " + fileName + '\n';
		throw exceptionMessage;
	}
}


#endif // !LOCAL_POS_SOLVER_IMPL
