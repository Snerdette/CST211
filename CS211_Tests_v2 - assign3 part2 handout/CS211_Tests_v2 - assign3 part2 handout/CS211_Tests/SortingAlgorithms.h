// SortingAlgorithms.h
// Pete Myers, OIT Winter 2020
// Classes that implement various sorting algorithsm
// Use ArrayList data structure
//
// Handout Assign3
//

#pragma once

#include "ArrayList.h"

template <class T> class Sorter
{
public:
	virtual void Sort(ArrayList<T>& list) = 0;
};


//
// Selection Sort
//

template <class T> class SelectionSort : public Sorter<T>
{
public:
	SelectionSort() { }

	virtual void Sort(ArrayList<T>& list)
	{
		// TODO SelectionSort::Sort()
	}
};


//
// MergeSort
//

template <class T> class MergeSort : public Sorter<T>
{
public:
	MergeSort() { }

	virtual void Sort(ArrayList<T>& list)
	{
		// TODO MergeSort::Sort()
	}
};


//
// HeapSort
//

template <class T> class HeapSort : public Sorter<T>
{
public:
	HeapSort() { }

	virtual void Sort(ArrayList<T>& list)
	{
		// TODO HeapSort::Sort()
	}
};

