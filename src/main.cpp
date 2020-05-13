#include "include/StrategyManagement.h"
#include "include/FolderGrouping.h"
#include "include/TypeGrouping.h"
#include <QApplication>
#include <QDir>
#include <QTextStream>
#include <QDebug>
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

	return QApplication::exec();
}