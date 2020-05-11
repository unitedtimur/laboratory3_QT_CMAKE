#include "include/AbstractStrategy.h"
#include "include/FolderGrouping.h"
#include "include/TypeGrouping.h"
#include <QApplication>
#include <QDir>
#include <QTextStream>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	AbstractStrategy* abstractStrategy = new FolderGrouping;
	abstractStrategy->explorer(QDir::currentPath());

	QTextStream(stdout) << "\n" << flush;

	delete abstractStrategy;

	abstractStrategy = new TypeGrouping;
	abstractStrategy->explorer(QDir::currentPath());

	delete abstractStrategy;

	QApplication::exec();

	return 0;
}