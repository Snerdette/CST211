// DictionaryTestSet.h
// Unit tests for dictionary data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"
#include "Dictionary.h"
#include "HashDictionary.h"
#include <functional>
#include <string>

typedef Dictionary<std::string, std::string>* (*DictionaryCreator)();

class StringHasher : public Hasher<std::string>
{
public:
	virtual int Hash(const std::string& key) const
	{
		std::size_t hc = std::hash<std::string>()(key);
		// the mask (0xzfffffff) is removing the bits making the keys negative.
		return (int)(hc & 0x7fffffff);
	}
};

StringHasher stringHasher;

Dictionary<std::string, std::string>* HashDictionaryCreator()
{
	return new HashDictionary<std::string, std::string>(&stringHasher);
}

class DictionaryTestSet : public TestSet
{
public:
	DictionaryTestSet(DictionaryCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Add/Count", "Add(), Count()", 1, AddCountTest, creator);
		AddTest("AddLots", "Add(), Contains(), Count()", 1, AddLotsTest, creator);
		AddTest("Get", "Add(), Get()", 1, GetTest, creator);
		AddTest("Remove", "Add(), Contains(), Count(), Remove()", 1, RemoveTest, creator);
		AddTest("Iterate", "Add(), Iterate(), HasNext(), Next()", 1, IterateTest, creator);
	}

private:
	static void AddCountTest(void* param)
	{
		DictionaryCreator dictionaryCreator = (DictionaryCreator)param;
		Dictionary<std::string, std::string>* dictionary = dictionaryCreator();

		Verify(dictionary->Count() == 0, "Count() == 0");
		dictionary->Add("foo", "one");
		Verify(dictionary->Count() == 1, "Count() == 1");
		dictionary->Add("bar", "two");
		Verify(dictionary->Count() == 2, "Count() == 2");
		dictionary->Add("blah", "three");
		Verify(dictionary->Count() == 3, "Count() == 3");

		delete dictionary;
	}

	static void AddLotsTest(void* param)
	{
		DictionaryCreator dictionaryCreator = (DictionaryCreator)param;
		Dictionary<std::string, std::string>* dictionary = dictionaryCreator();

		for (char c = 'a'; c <= 'z'; c++)
		{
			std::string s = "";
			s += c;
			dictionary->Add(s, s);
			Verify(dictionary->Contains(s), "Contains(" + s + ")");
		}
		Verify(dictionary->Count() == 26, "Count() == 26");

		delete dictionary;
	}

	static void GetTest(void* param)
	{
		DictionaryCreator dictionaryCreator = (DictionaryCreator)param;
		Dictionary<std::string, std::string>* dictionary = dictionaryCreator();

		dictionary->Add("foo", "one");
		dictionary->Add("bar", "two");
		dictionary->Add("blah", "three");

		Verify(dictionary->Get("foo") == "one", "Get(\"foo\") == \"one\"");
		Verify(dictionary->Get("bar") == "two", "Get(\"bar\") == \"two\"");
		Verify(dictionary->Get("blah") == "three", "Get(\"blah\") == \"three\"");
		
		delete dictionary;
	}

	static void RemoveTest(void* param)
	{
		DictionaryCreator dictionaryCreator = (DictionaryCreator)param;
		Dictionary<std::string, std::string>* dictionary = dictionaryCreator();

		dictionary->Add("foo", "one");
		dictionary->Add("bar", "two");
		dictionary->Add("blah", "three");
		
		dictionary->Remove("foo");
		Verify(!dictionary->Contains("foo"), "Contains(\"foo\") == false");
		Verify(dictionary->Count() == 2, "Count() == 2");

		dictionary->Remove("bar");
		Verify(!dictionary->Contains("bar"), "Contains(\"bar\") == false");
		Verify(dictionary->Count() == 1, "Count() == 1");

		dictionary->Remove("blah");
		Verify(!dictionary->Contains("blah"), "Contains(\"blah\") == false");
		Verify(dictionary->Count() == 0, "Count() == 0");

		delete dictionary;
	}

	static void IterateTest(void* param)
	{
		DictionaryCreator dictionaryCreator = (DictionaryCreator)param;
		Dictionary<std::string, std::string>* dictionary = dictionaryCreator();

		for (char c = 'a'; c <= 'z'; c++)
		{
			std::string s = "";
			s += c;
			dictionary->Add(s, s);
		}
		
		bool gotthem[26];
		for (int i = 0; i < 26; i++)
			gotthem[i] = false;

		DictionaryIterator<std::string, std::string>* iter = dictionary->Iterate();
		while (iter->HasNext())
		{
			Pair<std::string, std::string> p = iter->Next();
			gotthem[p.key[0] - 'a'] = true;
		}

		for (int i = 0; i < 26; i++)
		{
			std::string msg = "Didn't find '";
			msg += 'a' + i;
			msg += "'";
			Verify(gotthem[i], msg);
		}

		delete dictionary;
	}
};


