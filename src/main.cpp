#include <iostream>
#include<exception>

#include"TaskManger\task_manager.h"

int main()
{
	using std::cout;
	using std::endl;

	try
	{
		TaskManager<int> manager("a", "b");
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