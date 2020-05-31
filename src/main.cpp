#include "include/StrategyManagement.h"
#include "include/FolderGrouping.h"
#include "include/TypeGrouping.h"
#include "include/ConfigurationTest.h"
#include "include/FolderGroupingTest.h"
#include "include/TypeGroupingTest.h"
#include "include/Explorer.h"
#include <QApplication>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	// Проверка на утечку памяти
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	// Инициализируем управляющий класс и передаём туда стратегию для группировки по папкам
	//StrategyManagement* strategyManagement = new StrategyManagement(new FolderGrouping);
	//// Выполнение бизнес-логики
	//strategyManagement->doIt(QDir::currentPath(), QList<Data>());
	//// Выставление новое стратегии для группировки по типам
	//strategyManagement->setStrategy(new TypeGrouping);
	//// Выполнение бизнес-логики
	//strategyManagement->doIt(QDir::currentPath(), QList<Data>());
	//
	//// Очищение памяти
	//delete strategyManagement;
	
	// Запускаются тесты
	// ConfugurationTest configurationTest;
	// FolderGroupingTest folderGroupingTest; 
	// TypeGroupingTest typeGrupingTest;

	// Окно главной формы
	Explorer explorer;
	explorer.show();

	QApplication::exec();

	return 0;
}