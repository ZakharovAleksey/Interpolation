#pragma once

#ifndef LOCAL_POS_SOLVER
#define LOCAL_POS_SOLVER

//#include"../SecTaskManager/second_task_manager.h"

#include"../../FirstTask/Solver/interpolation.h"
#include"../../FirstTask/Solver/Linear/linear_interpolation.h"
#include"../../FirstTask/Solver/Quadratic/quadratic_interpolation.h"
#include"../../FirstTask/Solver/Qubic/qubic_interpolation.h"

template<typename T>
class LocalPositionSolver
{
public:
	LocalPositionSolver();
	~LocalPositionSolver();

	std::vector<std::pair<std::string, T>> CalculateLocalPositions(std::vector<std::tuple<std::string, std::string, int>> & tuples, double TIn);

	std::vector<Pair<T>> GetPairFromFile(std::ifstream & in, std::string const & fileName);


private:
	InterpolationSolver<T>* solverPtr_;
};



#include"local_pos_solver_impl.h"

#endif // !LOCAL_POS_SOLVER

