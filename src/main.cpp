#include <iostream>
#include<exception>

#include"FirstTask\TaskManger\task_manager.h"
#include"SecondTask\SecTaskManager\second_task_manager.h"

int main()
{
	using std::cout;
	using std::endl;

	try
	{
		//TaskManager<float> manager("a", "b", "c");
		//manager.Solve();

		SecondTaskManager<float> manager(1.4, "SecondTaskFiles/dots", "/SecondTaskFiles/conditions");
		manager.CalculateLocalPositions();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	catch (const std::string & ex)
	{
		std::cout << ex << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception!" << std::endl;
	}

	return 0;
}