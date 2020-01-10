// Tests.h
// Comprehensive unit tests for data structures in CST211 C++
// Winter 2020
// Pete Myers


#pragma once

#include <stdlib.h>

#include "ArrayList.h"
#include "LinkedList.h"

#include "TestBase.h"
#include "ListTestSet.h"


class Tester
{
public:
	Tester()
	{
	}

	void Run()
	{
		std::list<TestSet*> tests;

		tests.push_back(new ListTestSet(ArrayListCreator, STUDENT, "ArrayList Tests", ""));
		tests.push_back(new ListTestSet(LinkedListCreator, STUDENT, "LinkedList Tests", ""));
	
		for (std::list<TestSet*>::iterator iter = tests.begin(); iter != tests.end(); iter++)
		{
			(*iter)->Run();
		}

		std::cout << std::endl << "Test run complete!" << std::endl;
	}
};