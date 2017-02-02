#pragma once

#include<string>
#include<cstring>

#ifndef TASK_MANAGER
#define TASK_MANAGER

template<typename T>
struct Pair
{
	T arg;
	T value;

	Pair() : arg(T()), value(T()) { }

	Pair(T point, T value) : arg(point), value(value) { }
};


template<typename T>
class TaskManager
{
public:
	TaskManager(std::string fileName1, std::string fileName2);
	~TaskManager();

private:

	/// <summary>
	/// Function gets necessary data from appropriate file
	/// </summary>
	/// <param name="in"> ifstream </param>
	/// <param name="fileNumber"> Number of input file (1 or 2) </param>
	/// <param name="fileName"> Name of input file </param>
	void GetDataFromFile(std::ifstream & in, const int fileId, std::string const & fileName);




	std::string fileName1_;
	long int pointNumber1_;
	std::string fileName2_;
	long int pointNumber2_;
};

#include"task_manager_impl.h"

#endif // !TASK_MANAGER
