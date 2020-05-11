#include "include/FolderGrouping.h"
#include <QApplication>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	FolderGrouping folderGrouping;
	folderGrouping.explorer("E:\\");

	QCoreApplication::exec();

	return 0;
}