// OrderedTestSet.h
// Unit tests for OrderedList data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"

#include "OrderedList.h"
#include "BinaryTreeList.h"

typedef OrderedList<int>* (*OrderedListCreator)();

OrderedList<int>* BinaryTreeListCreator()
{
	return new BinaryTreeList<int>;
}

class OrderedListTestSet : public TestSet
{
public:
	OrderedListTestSet(OrderedListCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Add/Count", "Add(), Count()", 1, AddCountTest, creator);
		AddTest("Add/Iterator", "Add(), Count(), Begin(), iter->HasNext(), iter->Next()", 1, AddIteratorTest, creator);
		AddTest("Add Reverse Order", "Add(), Count(), Begin(), iter->HasNext(), iter->Next()", 1, AddReverseOrderTest, creator);
		AddTest("Add Out of Order", "Add(), Count(), Begin(), iter->HasNext(), iter->Next()", 1, AddOutOfOrderTest, creator);
		AddTest("Find 4 Items", "Add(), Count(), Find(obj), iter->HasNext(), iter->Next()", 1, Find4ItemsTest, creator);
		AddTest("Find 3 Items", "Add(), Count(), Find(obj), iter->HasNext(), iter->Next()", 1, Find3ItemsTest, creator);
		AddTest("Find 2 Items", "Add(), Count(), Find(obj), iter->HasNext(), iter->Next()", 1, Find2ItemsTest, creator);
		AddTest("Find 1 Item", "Add(), Count(), Find(obj), iter->HasNext(), iter->Next()", 1, Find1ItemTest, creator);
		AddTest("Find 0 Items", "Add(), Count(), Find(obj), iter->HasNext(), iter->Next()", 1, Find0ItemsTest, creator);
		AddTest("Remove", "Add(), Count(), Remove(), Begin(), iter->HasNext(), iter->Next()", 1, RemoveTest, creator);
	}

private:
	static void AddCountTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();

		Verify(list->Count() == 0, "Count() == 0");
		list->Add(1);
		Verify(list->Count() == 1, "Add(1), Count() == 1");
		list->Add(2);
		Verify(list->Count() == 2, "Add(2), Count() == 2");
		list->Add(3);
		Verify(list->Count() == 3, "Add(3), Count() == 3");

		delete list;
	}

	static void AddIteratorTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();

		list->Add(1);
		list->Add(2);
		list->Add(3);
		Verify(list->Count() == 3, "Add(1), Add(2), Add(3), Count() == 3");
		OrderedList<int>::OrderedListIterator* iter = list->Begin();
		int i;
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 4, "Didn't complete iteration!");

		delete iter;
		delete list;
	}

	static void AddReverseOrderTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();

		list->Add(3);
		list->Add(2);
		list->Add(1);
		Verify(list->Count() == 3, "Add(3), Add(2), Add(1), Count() == 3");
		OrderedList<int>::OrderedListIterator* iter = list->Begin();
		int i;
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 4, "Didn't complete iteration!");

		delete iter;
		delete list;
	}

	static void AddOutOfOrderTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();

		list->Add(2);
		list->Add(1);
		list->Add(4);
		list->Add(3);
		Verify(list->Count() == 4, "Add(2), Add(1), Add(4), Add(3), Count() == 4");
		OrderedList<int>::OrderedListIterator* iter = list->Begin();
		int i;
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 5, "Didn't complete iteration!");

		delete iter;
		delete list;
	}

	static void Find4ItemsTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();
		OrderedList<int>::OrderedListIterator* iter;
		int i;

		list->Add(2);
		list->Add(1);
		list->Add(4);
		list->Add(3);
		Verify(list->Count() == 4, "Add(2), Add(1), Add(4), Add(3), Count() == 4");

		iter = list->Find(1);
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 5, "Didn't complete iteration!");

		iter = list->Find(2);
		for (i = 2; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 5, "Didn't complete iteration!");

		iter = list->Find(3);
		for (i = 3; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 5, "Didn't complete iteration!");

		iter = list->Find(4);
		for (i = 4; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 5, "Didn't complete iteration!");

		iter = list->Find(5);
		Verify(iter == nullptr, "iter == nullptr");

		delete iter;
		delete list;
	}

	static void Find3ItemsTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();
		OrderedList<int>::OrderedListIterator* iter;
		int i;

		list->Add(2);
		list->Add(1);
		list->Add(3);
		Verify(list->Count() == 3, "Add(2), Add(1), Add(3), Count() == 3");

		iter = list->Find(1);
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 4, "Didn't complete iteration!");

		iter = list->Find(2);
		for (i = 2; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 4, "Didn't complete iteration!");

		iter = list->Find(3);
		for (i = 3; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 4, "Didn't complete iteration!");

		iter = list->Find(4);
		Verify(iter == nullptr, "iter == nullptr");

		delete iter;
		delete list;
	}

	static void Find2ItemsTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();
		OrderedList<int>::OrderedListIterator* iter;
		int i;

		list->Add(2);
		list->Add(1);
		Verify(list->Count() == 2, "Add(2), Add(1), Count() == 2");

		iter = list->Find(1);
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 3, "Didn't complete iteration!");

		iter = list->Find(2);
		for (i = 2; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 3, "Didn't complete iteration!");

		iter = list->Find(3);
		Verify(iter == nullptr, "iter == nullptr");

		delete iter;
		delete list;
	}

	static void Find1ItemTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();
		OrderedList<int>::OrderedListIterator* iter;
		int i;

		list->Add(1);
		Verify(list->Count() == 1, "Add(1), Count() == 1");

		iter = list->Find(1);
		for (i = 1; iter->HasNext(); i++)
		{
			int oi = iter->Next();
			Verify(oi == i, "iter->Next() == " + std::to_string(i));
		}
		Verify(i == 2, "Didn't complete iteration!");

		iter = list->Find(2);
		Verify(iter == nullptr, "iter == nullptr");

		delete iter;
		delete list;
	}

	static void Find0ItemsTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();
		OrderedList<int>::OrderedListIterator* iter;

		Verify(list->Count() == 0, "Count() == 0");

		iter = list->Find(1);
		Verify(iter == nullptr, "iter == nullptr");

		delete iter;
		delete list;
	}

	static void RemoveTest(void* param)
	{
		OrderedListCreator listCreator = (OrderedListCreator)param;
		OrderedList<int>* list = listCreator();
		OrderedList<int>::OrderedListIterator* iter;
		int i;

		// test removing the only item in the list
		list->Add(1);
		Verify(list->Count() == 1, "Add(1), Count() == 1");
		list->Remove(1);
		Verify(list->Count() == 0, "Remove(1), Count() == 0");
		
		// test removing an item with no children, that's on the left
		list->Add(2);
		list->Add(1);
		Verify(list->Count() == 2, "Add(2), Add(1), Count() == 2");
		list->Remove(1);
		Verify(list->Count() == 1, "Remove(1), Count() == 1");
		iter = list->Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 2, "iter->Next() == 2");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;

		// test removing an item with no children, that's on the right
		list->Add(3);
		Verify(list->Count() == 2, "Add(3), Count() == 2");
		list->Remove(3);
		Verify(list->Count() == 1, "Remove(3), Count() == 1");
		iter = list->Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 2, "iter->Next() == 2");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;

		// test removing an item with 1 child on it's right
		list->Add(3);
		list->Add(4);
		Verify(list->Count() == 3, "Add(3), Add(4), Count() == 3");
		list->Remove(3);
		Verify(list->Count() == 2, "Remove(3), Count() == 2");
		iter = list->Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 2, "iter->Next() == 2");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 4, "iter->Next() == 4");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;

		// test removing an item with 1 child on it's left
		list->Add(3);
		Verify(list->Count() == 3, "Add(3), Count() == 3");
		list->Remove(4);
		Verify(list->Count() == 2, "Remove(4), Count() == 2");
		iter = list->Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 2, "iter->Next() == 2");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 3, "iter->Next() == 3");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;

		// test removing an item with 2 children, where next node has no children
		list->Add(1);
		Verify(list->Count() == 3, "Add(1), Count() == 3");
		list->Remove(2);
		Verify(list->Count() == 2, "Remove(2), Count() == 2");
		iter = list->Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 1, "iter->Next() == 1");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 3, "iter->Next() == 3");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;

		// test removing an item with 2 children, where next node has a right child
		list->Add(4);
		list->Add(5);
		Verify(list->Count() == 4, "Add(4), Add(5), Count() == 4");
		list->Remove(3);
		Verify(list->Count() == 3, "Remove(3), Count() == 3");
		iter = list->Begin();
		Verify(iter != nullptr, "Begin() != nullptr");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 1, "iter->Next() == 1");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 4, "iter->Next() == 4");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == 5, "iter->Next() == 5");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;

		delete list;
	}
};

