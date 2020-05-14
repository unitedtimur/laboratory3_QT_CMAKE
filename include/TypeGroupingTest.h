#pragma once

#include "include/TypeGrouping.h"

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