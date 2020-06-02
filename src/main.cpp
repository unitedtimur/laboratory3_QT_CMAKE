#include "include/StrategyManagement.h"
#include "include/FolderGrouping.h"
#include "include/TypeGrouping.h"
#include "include/Explorer.h"
#include <QApplication>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	// Окно главной формы
    Explorer explorer;
    explorer.show();

	QApplication::exec();
	
	return 0;
}
