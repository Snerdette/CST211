// SortingAlgorithmsTestSet.h
// Unit tests for sorting algorithms in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"
#include "ArrayList.h"
#include "SortingAlgorithms.h"

typedef Sorter<int>* (*SorterCreator)();

Sorter<int>* SelectionSortCreator()
{
	return new SelectionSort<int>();
}

Sorter<int>* MergeSortCreator()
{
	return new MergeSort<int>();
}

Sorter<int>* HeapSortCreator()
{
	return new HeapSort<int>();
}

class SortingAlgorithmTestSet : public TestSet
{
public:
	SortingAlgorithmTestSet(SorterCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Empty", "Sort empty list", 1, EmptyTest, creator);
		AddTest("One Item", "Sort list with 1 item", 1, OneTest, creator);
		AddTest("In Order", "Sort list starting already in order", 1, InOrderTest, creator);
		AddTest("Reverse Order", "Sort list starting in reverse order", 1, ReverseOrderTest, creator);
		AddTest("Random Order", "Sort list starting in random order", 1, RandomOrderTest, creator);
	}

private:
	static void EmptyTest(void* param)
	{
		SorterCreator sortCreator = (SorterCreator)param;
		Sorter<int>* sorter = sortCreator();

		ArrayList<int> list;
		
		sorter->Sort(list);
		Verify(list.Count() == 0, "Sort(), Count() == 0");
		
		delete sorter;
	}

	static void OneTest(void* param)
	{
		SorterCreator sortCreator = (SorterCreator)param;
		Sorter<int>* sorter = sortCreator();

		ArrayList<int> list;
		list.Append(1);

		sorter->Sort(list);
		Verify(list.Count() == 1, "Sort(), Count() == 1");
		Verify(list.Get(0) == 1, "Get(0) == 1");

		delete sorter;
	}

	static void InOrderTest(void* param)
	{
		SorterCreator sortCreator = (SorterCreator)param;
		Sorter<int>* sorter = sortCreator();

		ArrayList<int> list;
		list.Append(1);
		list.Append(2);
		list.Append(3);
		list.Append(4);
		list.Append(5);

		sorter->Sort(list);
		Verify(list.Count() == 5, "Sort(), Count() == 5");
		ArrayList<int>::ListIterator * iter = list.Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		for (int i = 1; i <= 5; i++)
		{
			Verify(iter->HasNext(), "iter->HasNext()");
			char msg[256];
			sprintf_s(msg, "iter->Next == %d", i);
			Verify(iter->Next() == i, msg);
		}
		
		delete iter;
		delete sorter;
	}

	static void ReverseOrderTest(void* param)
	{
		SorterCreator sortCreator = (SorterCreator)param;
		Sorter<int>* sorter = sortCreator();

		ArrayList<int> list;
		list.Append(5);
		list.Append(4);
		list.Append(3);
		list.Append(2);
		list.Append(1);

		sorter->Sort(list);
		Verify(list.Count() == 5, "Sort(), Count() == 5");
		ArrayList<int>::ListIterator* iter = list.Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		for (int i = 1; i <= 5; i++)
		{
			Verify(iter->HasNext(), "iter->HasNext()");
			char msg[256];
			sprintf_s(msg, "iter->Next == %d", i);
			Verify(iter->Next() == i, msg);
		}

		delete iter;
		delete sorter;
	}

	static void RandomOrderTest(void* param)
	{
		SorterCreator sortCreator = (SorterCreator)param;
		Sorter<int>* sorter = sortCreator();

		ArrayList<int> list;
		list.Append(3);
		list.Append(5);
		list.Append(2);
		list.Append(1);
		list.Append(4);

		sorter->Sort(list);
		Verify(list.Count() == 5, "Sort(), Count() == 5");
		ArrayList<int>::ListIterator* iter = list.Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		for (int i = 1; i <= 5; i++)
		{
			Verify(iter->HasNext(), "iter->HasNext()");
			char msg[256];
			sprintf_s(msg, "iter->Next == %d", i);
			Verify(iter->Next() == i, msg);
		}

		delete iter;
		delete sorter;
	}
};


