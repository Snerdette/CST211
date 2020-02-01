// Tests.h
// Comprehensive unit tests for data structures in CST211 C++
// Winter 2020
// Pete Myers
//
// Assign2 handout
//


#pragma once

#include <stdlib.h>

#include "ArrayList.h"
#include "LinkedList.h"
#include "ArrayListStack.h"
#include "OrderedList.h"
#include "BinaryTreeList.h"
#include "CircularArrayQueue.h"

#include "TestBase.h"
#include "ListTestSet.h"
#include "StackTestSet.h"
#include "OrderedListTestSet.h"
#include "QueueTestSet.h"


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
		tests.push_back(new StackTestSet(ArrayListStackCreator, STUDENT, "ArraryListStack Tests", ""));
		tests.push_back(new QueueTestSet(CircularArrayQueueCreator, STUDENT, "CircularArrayQueue Tests", ""));
		tests.push_back(new OrderedListTestSet(BinaryTreeListCreator, STUDENT, "BinaryTreeList Tests", ""));
	
		for (std::list<TestSet*>::iterator iter = tests.begin(); iter != tests.end(); iter++)
		{
			(*iter)->Run();
		}

		std::cout << std::endl << "Test run complete!" << std::endl;
	}
};