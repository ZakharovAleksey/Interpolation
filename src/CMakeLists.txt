cmake_minimum_required(VERSION 3.5)

#set(PATH_SOLVER "Solver")
#set(PATH_LINEAR_SOLVER "Solver/Linear")
#set(PATH_QUADRATIC_SOLVER "Solver/Quadratic")
#set(PATH_QUBIC_SOLVER "Solver/Qubic")
#set(PATH_MANAGER "TaskManger")

set(
	source_list
	"Solver/iInterpolation.h"
	"Solver/interpolation.h"
	"Solver/interpolation_impl.h"
	"Solver/Linear/linear_interpolation.h"
	"Solver/Linear/linear_interpolation_impl.h"
	"Solver/Quadratic/quadratic_interpolation.h"
	"Solver/Quadratic/quadratic_interpolation_impl.h"
	"Solver/Qubic/qubic_interpolation.h"
	"Solver/Qubic/qubic_interpolation_impl.h"
	"TaskManger/task_manager.h"
	"TaskManger/task_manager_impl.h"
	"main.cpp"
)

add_executable(${PROJECT_NAME} ${source_list})

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
