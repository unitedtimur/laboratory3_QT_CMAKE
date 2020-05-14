#include "include/TypeGroupingTest.h"
#include "include/Configuration.h"

TypeGroupingTest::TypeGroupingTest()
{
	this->explorerTest();
	this->setMapTest();
	this->getAllFilesTest();
	this->getInformationByTypePercentageOfTotalTest();
}

void TypeGroupingTest::explorerTest()
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

void TypeGroupingTest::setMapTest()
{
	// Тест проверяект возвращаемые значения функции setMap()
	try
	{
		QMap<QString, qint64> from;
		{
			from.insert("1", 228);
			from.insert("2", 322);
			from.insert("3", 404);
		}

		QMap<QString, qint64> to;

		setMap(from, to);

		QVector<QString> keys; 

		// Получаем ключи
		for (const auto& key : to.keys())
			keys.push_back(key);

		// Проверяем ключи
		if (!(keys[0] == "1"))
			throw std::exception("ERROR: Wrong key!");
		if (!(keys[1] == "2"))
			throw std::exception("ERROR: Wrong key!");
		if (!(keys[2] == "3"))
			throw std::exception("ERROR: Wrong key!");

		QVector<qint64> values;

		// Получаем значения
		for (const auto& value : to.values())
			values.push_back(value);

		if (!(values[0] == 228))
			throw std::exception("ERROR: Wrong value!");
		if (!(values[1] == 322))
			throw std::exception("ERROR: Wrong value!");
		if (!(values[2] == 404))
			throw std::exception("ERROR: Wrong value!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}

void TypeGroupingTest::getAllFilesTest()
{
	// Тест проверяект возвращаемые значения функции getAllFiles()
	try
	{
		// Выполняем саму функцию
		const auto testFiles = "../QT Laboratory3/src/Tests/FolderGrouping";
		const auto filesAndFoldersList = getAllFiles(testFiles);

		if (!(filesAndFoldersList.size() == 15)) // 15 файлов
			throw std::exception("ERROR: Files size is not 15!");

		QVector<QString> keys;

		// Получаем ключи
		for (const auto& key : filesAndFoldersList.keys())
			keys.push_back(key);

		// Проверяем ключи
		if (!(keys[0].endsWith("QT Laboratory3/src/Tests/FolderGrouping/First/splash.png")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[1].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/glazedlists_java15.jar")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[2].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/glazedlists_java15.rights")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[3].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/jaccess-1_4.jar")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[4].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/jdom.jar")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[5].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/jdom.rights")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[6].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/mwaws_client.jar")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[7].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/xerces.rights")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[8].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Second/xercesImpl.jar")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[9].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third/blas.h")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[10].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third/blascompat32.h")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[11].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third/emlrt.h")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[12].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third/engine.h")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[13].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third/fintrf.h")))
			throw std::exception("ERROR: Wrong name of file!");
		if (!(keys[14].endsWith("QT Laboratory3/src/Tests/FolderGrouping/Third/io64.h")))
			throw std::exception("ERROR: Wrong name of file!");

		QVector<qint64> values;

		// Получаем значения
		for (const auto& value : filesAndFoldersList.values())
			values.push_back(value);

		if (!(values[0] == 116431))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[1] == 747719))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[2] == 783))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[3] == 47329))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[4] == 153253))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[5] == 2564))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[6] == 468229))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[7] == 16826))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[8] == 1223708))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[9] == 34861))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[10] == 14113))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[11] == 45214))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[12] == 2612))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[13] == 17121))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[14] == 3129))
			throw std::exception("ERROR: Wrong value of file!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}

void TypeGroupingTest::getInformationByTypePercentageOfTotalTest()
{
	// Тест проверяет возвращаемое значение функции getInformationByTypePercentageOfTotal()
	try
	{
		const auto testFiles = "../QT Laboratory3/src/Tests/FolderGrouping";
		const auto totalSize = Configuration::GetTotalSize(testFiles);
		const auto filesAndFoldersList = getAllFiles(testFiles);
		const auto filesAndFoldersListPercentage = getInformationByTypePercentageOfTotal(totalSize, filesAndFoldersList);

		QVector<QString> keys;

		// Получаем ключи из QMap
		for (const auto& key : filesAndFoldersListPercentage.keys())
			keys.push_back(key);

		if (!(keys[0] == "h"))
			throw std::exception("ERROR: Wrong key of file!");
		if (!(keys[1] == "jar"))
			throw std::exception("ERROR: Wrong key of file!");
		if (!(keys[2] == "png"))
			throw std::exception("ERROR: Wrong key of file!");
		if (!(keys[3] == "rights"))
			throw std::exception("ERROR: Wrong key of file!");

		QVector<double> values;

		// Получаем значения из QMap
		for (const auto& value : filesAndFoldersListPercentage.values())
			values.push_back(value);

		// Проверяем ключи
		if (!(values[0] == 4.0447259261921316))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[1] == 91.234849123602402))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[2] == 4.0233360470950537))
			throw std::exception("ERROR: Wrong value of file!");
		if (!(values[3] == 0.69708890311041327))
			throw std::exception("ERROR: Wrong value of file!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}
