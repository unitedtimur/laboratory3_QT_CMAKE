#include "include/FolderGrouping.h"
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

FolderGrouping::FolderGrouping() : 
	cin(new QTextStream),
	cout(new QTextStream)
{
}

FolderGrouping::~FolderGrouping()
{
	delete cin;
	delete cout;
}

void* FolderGrouping::explorer(const QString& path)
{
	QFileInfo file(path);

	if (!file.exists() && !file.isReadable())
		return nullptr;

	if (file.isDir())
	{
		quint64 totalSize = TotalSize().get(file.absoluteFilePath());

		qDebug() << totalSize;


		for (const auto& it : QDir(file.absoluteFilePath()).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
		{

		}
	}

	return nullptr;
}

quint64 FolderGrouping::totalSize(const QString& path) noexcept
{
	static quint64 totalSize = 0;

	for (const auto& it : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
		(it.isDir() /*&& !it.isSymLink()*/) ? this->totalSize(it.absoluteFilePath()) : totalSize += it.size();

	return totalSize;
}
