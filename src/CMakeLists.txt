cmake_minimum_required(VERSION 3.5)

#set(PATH_SOLVER "Solver")
#set(PATH_LINEAR_SOLVER "Solver/Linear")
#set(PATH_QUADRATIC_SOLVER "Solver/Quadratic")
#set(PATH_QUBIC_SOLVER "Solver/Qubic")
#set(PATH_MANAGER "TaskManger")

set(
	source_list
	"FirstTask/Solver/iInterpolation.h"
	"FirstTask/Solver/interpolation.h"
	"FirstTask/Solver/interpolation_impl.h"
	"FirstTask/Solver/Linear/linear_interpolation.h"
	"FirstTask/Solver/Linear/linear_interpolation_impl.h"
	"FirstTask/Solver/Quadratic/quadratic_interpolation.h"
	"FirstTask/Solver/Quadratic/quadratic_interpolation_impl.h"
	"FirstTask/Solver/Qubic/qubic_interpolation.h"
	"FirstTask/Solver/Qubic/qubic_interpolation_impl.h"
	"FirstTask/TaskManger/task_manager.h"
	"FirstTask/TaskManger/task_manager_impl.h"
	"SecondTask/GlobalPosSolver/global_pos_solver.h"
	"SecondTask/GlobalPosSolver/global_pos_solver_impl.h"
	"SecondTask/LocalPosSolver/local_pos_solver.h"
	"SecondTask/LocalPosSolver/local_pos_solver_impl.h"
	"SecondTask/SecTaskManager/second_task_manager.h"
	"SecondTask/SecTaskManager/second_task_manager_impl.h"
	"MainManager/main_manager.h"
	"MainManager/main_manager_impl.h"
	"main.cpp"
)

add_executable(${PROJECT_NAME} ${source_list})

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
