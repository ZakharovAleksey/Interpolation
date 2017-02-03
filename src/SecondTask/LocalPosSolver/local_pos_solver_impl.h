#include "local_pos_solver.h"
#pragma once

#ifndef LOCAL_POS_SOLVER_IMPL
#define LOCAL_POS_SOLVER_IMPL

template<typename T>
LocalPositionSolver<T>::LocalPositionSolver() : solverPtr_(nullptr) {}

template<typename T>
LocalPositionSolver<T>::~LocalPositionSolver() {}

template<typename T>
inline std::vector<std::pair<std::string, T>> LocalPositionSolver<T>::CalculateLocalPositions(std::vector<std::tuple<std::string, std::string, int>>& tuples, double TIn)
{
	std::cout << "Here\n";
	std::ifstream in;
	std::vector<Pair<T>> dotPosition;
	std::vector<std::pair<std::string, T>> resultVector;

	for (auto curTuple : tuples)
	{
		switch (std::get<2>(curTuple))
		{
		case 1:
			solverPtr_ = new LinearInterpolationSolver<T>();
			break;
		case 2:
			solverPtr_ = new QuadraticInterpolationSolver<T>();
			break;
		case 3:
			solverPtr_ = new QubicInterpolationSolver<T>();
			break;
		default:
			std::cout << "Error! Wrong input interpolation order! Could not create apropriate solver!\n";
			break;
		}

		dotPosition = GetPairFromFile(in, std::get<1>(curTuple));
		solverPtr_->SetInutPairs(dotPosition);
		solverPtr_->BuildInterpolation();


		std::pair<std::string, T> res;
		res = std::make_pair(std::get<0>(curTuple), solverPtr_->FindInterpolationValue(TIn));
		
		std::cout << std::get<0>(curTuple) << " -> local: " << solverPtr_->FindInterpolationValue(TIn) << std::endl;

		resultVector.push_back(res);

		delete solverPtr_;

	}

	return resultVector;
}

template<typename T>
inline std::vector<Pair<T>> LocalPositionSolver<T>::GetPairFromFile(std::ifstream & in, std::string const & fileName)
{
	in.open("SecondTaskFiles/" + fileName);
	
	int dotsNumber;
	
	if (in.is_open())
	{
		// Read number of points in the file
		in >> dotsNumber;
	
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
