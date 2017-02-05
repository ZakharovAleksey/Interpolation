#pragma once

#ifndef MAIN_MANAGER_IMPL
#define MAIN_MANAGER_IMPL

#include"main_manager.h"

#include<string>

template<typename T>
MainManager<T>::MainManager() : firstTaskPtr_(nullptr), secondTaskPtr_(nullptr) { }

template<typename T>
MainManager<T>::~MainManager() { }

template<typename T>
inline void MainManager<T>::TaskLoopExecution()
{
	std::cout << "Welcome to Nekki testing tasks solver!\n";
	bool isExecuted = true;

	while (isExecuted)
	{
		std::cout << "\nChoose number of task :\n" <<
			"  0 - Check tests\n" <<
			"  1 - First task (Interpolation of a given set of points.)\n" <<
			"  2 - Second task(Definition of global coordinates of points in a given time.)\n" <<
			" -1 - Quit.\nYour input:  ";

		int userInput = -2;
		bool isCorrestInput = false;

		while (!isCorrestInput)
		{
			std::cin >> userInput;
			if (!std::cin)
			{
				// Clear all user input
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				std::cout << "Wrong input! Please input 0(Test) 1(First task) 2(Second task).\nYour input:  ";
				continue;
			}

			if (userInput == 0 || userInput == 1 || userInput == 2 || userInput == -1)
				isCorrestInput = true;
			else
				std::cout << "Wrong input! Please input 0(Test) 1(First task) 2(Second task).\nYour input:  ";

		}

		switch (userInput)
		{
		case 0:
			OnTest();
			break;
		case 1:
			OnFirstTask();
			break;
		case 2:
			OnSecondTask();
			break;
		case -1:
			std::cout << "Goodbye!\n";
			return;
			break;
		default:
			break;
		}
	}


}

template<typename T>
inline void MainManager<T>::OnTest()
{
	// Execute the test of the first task
	firstTaskPtr_ = std::unique_ptr<TaskManager<T>>(new TaskManager<T> ("test_first", "test_second", "test_output"));
	firstTaskPtr_->Solve();

	// Execute the test of the second task
	secondTaskPtr_ = std::unique_ptr<SecondTaskManager<T>>(new SecondTaskManager<T>(1.4, "SecondTaskFiles/dots", "SecondTaskFiles/conditions"));
	secondTaskPtr_->CalculateGlobalPositions();

	std::cout << "\nTests for both tasks successfully completed!\n";
}

template<typename T>
inline void MainManager<T>::OnFirstTask()
{
	std::cout << "\n!!! YOUR INPUT FILES SHOULD BE LOCATED IN THE DIRECTURY: \"\\src\\FirstTaskFiles\\\" !!!\n";

	std::string firstFileName;
	std::cout << "1. Input name of first input file: "; std::cin >> firstFileName;

	std::string secondFileName;
	std::cout << "2. Input name of second input file: "; std::cin >> secondFileName;

	std::string outputFileName;
	std::cout << "3. Input name of output file: "; std::cin >> outputFileName;

	// Execute the the first task
	firstTaskPtr_.reset(new TaskManager<T>(firstFileName, secondFileName, outputFileName));
	firstTaskPtr_->Solve();

}

template<typename T>
inline void MainManager<T>::OnSecondTask()
{
	std::cout << "!!! Your input files should be located in a directory: \"\\src\\SecondTaskFiles\\\" !!!\n";

	bool isInputCorrect = false;
	T time;

	while (!isInputCorrect)
	{
		std::cout << "Input Time: "; std::cin >> time;

		if (!std::cin)
		{
			// Clear all user input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Wrong input! Input float number\nInput Time: ";
			continue;
		}
		else
			isInputCorrect = true;
	}

	std::string firstFileName;
	std::cout << "1. Input name of first input file: "; std::cin >> firstFileName;

	std::string secondFileName;
	std::cout << "2. Input name of second input file: "; std::cin >> secondFileName;
	
	// Execute the second task
	secondTaskPtr_.reset( new SecondTaskManager<T>(time, "SecondTaskFiles/" + firstFileName, "SecondTaskFiles/" + secondFileName));
	secondTaskPtr_->CalculateGlobalPositions();
}


#endif // !MAIN_MANAGER_IMPL