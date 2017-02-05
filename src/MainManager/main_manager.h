#pragma once

#ifndef MAIN_MANAGER
#define MAIN_MANAGER

#include"../FirstTask/TaskManger/task_manager.h"
#include"../SecondTask/SecTaskManager/second_task_manager.h"

#include<memory>

template<typename T>
class MainManager
{
public:
	MainManager();
	~MainManager();

	// Main programm loop
	void TaskLoopExecution();

private:
	void OnTest();
	void OnFirstTask();
	void OnSecondTask();

	// Pointer to the first task manager
	std::unique_ptr<TaskManager<T>> firstTaskPtr_;
	// Pointer to the second task manager
	std::unique_ptr<SecondTaskManager<T>> secondTaskPtr_;

};


#include"main_manager_impl.h"

#endif // !MAIN_MANAGER
