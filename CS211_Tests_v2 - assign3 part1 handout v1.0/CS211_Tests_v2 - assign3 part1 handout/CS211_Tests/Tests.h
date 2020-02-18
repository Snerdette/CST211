// Tests.h
// Comprehensive unit tests for data structures in CST211 C++
// Winter 2020
// Pete Myers


#pragma once

#include <stdlib.h>

#include "ArrayList.h"
#include "LinkedList.h"
#include "ArrayListStack.h"
#include "OrderedList.h"
#include "BinaryTreeList.h"
#include "CircularArrayQueue.h"
#include "SortingAlgorithms.h"

#include "TestBase.h"
#include "ListTestSet.h"
#include "StackTestSet.h"
#include "OrderedListTestSet.h"
#include "QueueTestSet.h"
#include "SortingAlgorithmsTestSet.h"





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
		tests.push_back(new SortingAlgorithmTestSet(SelectionSortCreator, STUDENT, "Selection Sort Tests", ""));
		tests.push_back(new SortingAlgorithmTestSet(MergeSortCreator, STUDENT, "Merge Sort Tests", ""));
		tests.push_back(new SortingAlgorithmTestSet(HeapSortCreator, STUDENT, "Heap Sort Tests", ""));
		
		for (std::list<TestSet*>::iterator iter = tests.begin(); iter != tests.end(); iter++)
		{
			(*iter)->Run();
		}

		std::cout << std::endl << "Test run complete!" << std::endl;
	}
};