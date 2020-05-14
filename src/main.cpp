#include "include/StrategyManagement.h"
#include "include/FolderGrouping.h"
#include "include/TypeGrouping.h"
#include "include/ConfigurationTest.h"
#include "include/FolderGroupingTest.h"
#include "include/TypeGroupingTest.h"
#include <QApplication>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	StrategyManagement* strategyManagement = new StrategyManagement(new FolderGrouping);
	strategyManagement->doIt(QDir::currentPath());
	strategyManagement->setStrategy(new TypeGrouping);
	strategyManagement->doIt(QDir::currentPath());

	delete strategyManagement;

	// Запускаются тесты
	ConfugurationTest configurationTest;
	FolderGroupingTest folderGroupingTest; 
	TypeGroupingTest typeGrupingTest;

	return QApplication::exec();
}