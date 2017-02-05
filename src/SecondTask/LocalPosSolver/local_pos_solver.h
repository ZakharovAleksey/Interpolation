#pragma once

#ifndef LOCAL_POS_SOLVER
#define LOCAL_POS_SOLVER

#include"../../FirstTask/Solver/interpolation.h"
#include"../../FirstTask/Solver/Linear/linear_interpolation.h"
#include"../../FirstTask/Solver/Quadratic/quadratic_interpolation.h"
#include"../../FirstTask/Solver/Qubic/qubic_interpolation.h"

#include<map>
#include<memory>

// Class calculate local position of all dots
template<typename T>
class LocalPositionSolver
{
public:
	LocalPositionSolver();
	~LocalPositionSolver();

	typedef std::tuple<std::string, std::string, int> Tuple;

	// Calculate local position of all dots
	std::map<std::string, T> CalculateLocalPositions(const std::vector<Tuple> & tuples, const double TIn);

	// Get all time evolution for a single dot according to it own data file
	std::vector<Pair<T>> GetDotTimeEvolution(std::ifstream & in, std::string const & fileName);


private:
	// Pointer to interpolation solver
	std::unique_ptr<InterpolationSolver<T>> solverPtr_;
};



#include"local_pos_solver_impl.h"

#endif // !LOCAL_POS_SOLVER

