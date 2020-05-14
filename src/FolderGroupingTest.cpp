#include "include/FolderGroupingTest.h"
#include "include/Configuration.h"

FolderGroupingTest::FolderGroupingTest()
{
	this->explorerTest();
	this->getFilesAndFoldersTest();
	this->getInformationByFoldersPercentageOfTotalTest();
}

void FolderGroupingTest::explorerTest()
{
	// Тест проверяет возвращаемое значение функции explorer()
	try
	{
		if (!explorer("../QT Laboratory3/src/Tests/FolderGrouping"))
			throw std::exception("ERROR: Wrong value of function explorer!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}

void FolderGroupingTest::getFilesAndFoldersTest()
{
	// Тест проверяект возвращаемые значения функции getFilesAndFolders()
	try
	{
		// Выполняем саму функцию
		const auto testFiles = "../QT Laboratory3/src/Tests/FolderGrouping";
		const auto filesAndFoldersList = getFilesAndFolders(testFiles);

		if (!(filesAndFoldersList.size() == 3)) // 3 папки
			throw std::exception("ERROR: Folder size is not 3!");

		QVector<QString> keys;

		// Получаем ключи из полученного QMap
		for (const auto& key : filesAndFoldersList.keys())
			keys.push_back(key);

		// Проверяем ключи
		if (!(keys[0].endsWith("QT Laboratory3/src/Tests/FolderGrouping/First")))
			throw std::exception("ERROR: Wrong name of folder!");
		if (!(keys[1].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second")))
			throw std::exception("ERROR: Wrong name of folder!");
		if (!(keys[2].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third")))
			throw std::exception("ERROR: Wrong name of folder!");

		QVector<double> values;

		// Получаем значения из полученного QMap
		for (const auto& value : filesAndFoldersList.values())
			values.push_back(value);

		// Проверяем значения
		if (!(values[0] == 116431.00000000000))
			throw std::exception("ERROR: Wrong value of folder!");
		if (!(values[1] == 2660411.0000000000))
			throw std::exception("ERROR: Wrong value of folder!");
		if (!(values[2] == 117050.00000000000))
			throw std::exception("ERROR: Wrong value of folder!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}

void FolderGroupingTest::getInformationByFoldersPercentageOfTotalTest()
{
	// Тест проверяет возвращаемое значение функции getInformationByFoldersPercentageOfTotal()
	try
	{
		const auto testFiles = "../QT Laboratory3/src/Tests/FolderGrouping";
		const auto totalSize = Configuration::GetTotalSize(testFiles);
		const auto filesAndFoldersList = getFilesAndFolders(testFiles);
		const auto filesAndFoldersListPercentage = getInformationByFoldersPercentageOfTotal(totalSize, filesAndFoldersList);
		
		QVector<double> values;

		// Получаем значения из QMap
		for (const auto& value : filesAndFoldersListPercentage.values())
			values.push_back(value);

		// Проверяем ключи
		if (!(values[0] == 4.0233360470950537))
			throw std::exception("ERROR: Wrong value of folder!");
		if (!(values[1] == 91.931938026712814))
			throw std::exception("ERROR: Wrong value of folder!");
		if (!(values[2] == 4.0447259261921316))
			throw std::exception("ERROR: Wrong value of folder!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}
