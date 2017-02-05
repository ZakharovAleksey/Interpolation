#include <iostream>
#include<exception>

#include"MainManager\main_manager.h"

int main()
{
	using std::cout;
	using std::endl;

	try
	{
		MainManager<double> mal;
		mal.TaskLoopExecution();
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