#pragma once

#include "include/FolderGrouping.h"

class FolderGroupingTest final : public FolderGrouping
{
public:
	explicit FolderGroupingTest();
	~FolderGroupingTest() = default;

private:
	void explorerTest();
	void getFilesAndFoldersTest();
	void getInformationByFoldersPercentageOfTotalTest();
};