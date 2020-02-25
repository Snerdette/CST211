// HashTestSet.h
// Unit tests for set data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"
#include "Set.h"
#include "HashSet.h"
#include <functional>
#include <string>

typedef Set<std::string>* (*SetCreator)();

Set<std::string>* HashSetCreator()
{
	// NOTE: reuses StringHasher from HashSetTestSet.h
	return new HashSet<std::string>(&stringHasher);
}

class SetTestSet : public TestSet
{
public:
	SetTestSet(SetCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Add/Count", "Add(), Count()", 1, AddCountTest, creator);
		AddTest("AddLots", "Add(), Contains(), Count()", 1, AddLotsTest, creator);
		AddTest("Remove", "Add(), Contains(), Count(), Remove()", 1, RemoveTest, creator);
		AddTest("Iterate", "Add(), Iterate(), HasNext(), Next()", 1, IterateTest, creator);
	}

private:
	static void AddCountTest(void* param)
	{
		SetCreator setCreator = (SetCreator)param;
		Set<std::string>* set = setCreator();

		Verify(set->Count() == 0, "Count() == 0");
		set->Add("foo");
		Verify(set->Count() == 1, "Count() == 1");
		set->Add("bar");
		Verify(set->Count() == 2, "Count() == 2");
		set->Add("blah");
		Verify(set->Count() == 3, "Count() == 3");

		delete set;
	}

	static void AddLotsTest(void* param)
	{
		SetCreator setCreator = (SetCreator)param;
		Set<std::string>* set = setCreator();

		for (char c = 'a'; c <= 'z'; c++)
		{
			std::string s = "";
			s += c;
			set->Add(s);
			Verify(set->Contains(s), "Contains(" + s + ")");
		}
		Verify(set->Count() == 26, "Count() == 26");

		delete set;
	}

	static void RemoveTest(void* param)
	{
		SetCreator setCreator = (SetCreator)param;
		Set<std::string>* set = setCreator();

		set->Add("foo");
		set->Add("bar");
		set->Add("blah");
		
		set->Remove("foo");
		Verify(!set->Contains("foo"), "Contains(\"foo\") == false");
		Verify(set->Count() == 2, "Count() == 2");

		set->Remove("bar");
		Verify(!set->Contains("bar"), "Contains(\"bar\") == false");
		Verify(set->Count() == 1, "Count() == 1");

		set->Remove("blah");
		Verify(!set->Contains("blah"), "Contains(\"blah\") == false");
		Verify(set->Count() == 0, "Count() == 0");

		delete set;
	}

	static void IterateTest(void* param)
	{
		SetCreator setCreator = (SetCreator)param;
		Set<std::string>* set = setCreator();

		for (char c = 'a'; c <= 'z'; c++)
		{
			std::string s = "";
			s += c;
			set->Add(s);
		}

		bool gotthem[26];
		for (int i = 0; i < 26; i++)
			gotthem[i] = false;

		SetIterator<std::string>* iter = set->Iterate();
		while (iter->HasNext())
		{
			std::string s = iter->Next();
			gotthem[s[0] - 'a'] = true;
		}

		for (int i = 0; i < 26; i++)
		{
			std::string msg = "Didn't find '";
			msg += 'a' + i;
			msg += "'";
			Verify(gotthem[i], msg);
		}

		delete set;
	}
};


