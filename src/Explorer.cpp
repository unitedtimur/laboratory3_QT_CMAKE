#include "include/Explorer.h"

#include <QDir>
#include <qtextstream.h>

Explorer::Explorer() : 
	dir(new QDir)
{
	dir->setPath(QDir::currentPath());
}

Explorer::~Explorer()
{
	delete dir;
}

void Explorer::bypass(const QString& name) noexcept
{
	for (const auto& it : QDir(name).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
		(it.isDir() && !it.isSymLink()) ? this->bypass(it.absoluteFilePath()) : (QTextStream(stdout) << it.fileName() << " " << it.size() << " bytes\n");
}