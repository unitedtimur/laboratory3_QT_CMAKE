#include "include/ConfigurationTest.h"
#include "include/Configuration.h"

ConfugurationTest::ConfugurationTest()
{
	this->GetTotalSizeTest();
}

void ConfugurationTest::GetTotalSizeTest()
{
	// Тест проверяет возвращаемое значение функции GetTotalSize()
	try
	{
		// Выполняем саму функцию
		const auto testFiles = "../QT Laboratory3/src/Tests/FolderGrouping";
		const auto totalSize = Configuration::GetTotalSize(testFiles);

		if (!(totalSize == 2893892))
			throw std::exception("ERROR: Wrong total size!");

		QTextStream(stdout) << QString(__FUNCTION__) + " OK" << endl;
	}
	catch (const std::exception& ex)
	{
		QTextStream(stdout) << ex.what() << endl;
		QTextStream(stdout) << QString(__FUNCTION__) + " BAD" << endl;
	}
}