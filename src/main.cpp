#include "include/Explorer.h"
#include "include/FolderGrouping.h"
#include <QApplication>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	FolderGrouping folderGrouping;
	folderGrouping.explorer(QDir::currentPath());


	QCoreApplication::exec();


	return 0;
}