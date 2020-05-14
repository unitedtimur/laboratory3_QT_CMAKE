#pragma once

#include "include/TypeGrouping.h"

// Аналогичный TypeGrouping ( тестовый класс )
class TypeGroupingTest : public TypeGrouping
{
public:
	explicit TypeGroupingTest();
	~TypeGroupingTest() = default;

private:
	void explorerTest();
	void setMapTest();
	void getAllFilesTest();
	void getInformationByTypePercentageOfTotalTest();
};