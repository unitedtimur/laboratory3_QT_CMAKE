#include "include/FolderGrouping.h"
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

bool FolderGrouping::explorer(const QString& path)
{
	QFileInfo file(path);

	if (!file.exists() && !file.isReadable())
		return false;

	const auto absolutePath = file.absoluteFilePath();
	const auto totalSize = this->getTotalSize(absolutePath);
	const auto filesAndFoldersList = this->getFilesAndFolders(absolutePath);
	const auto filesAndFoldersListPercentage = this->getInformationPercentageOfTotal(totalSize, filesAndFoldersList);
	this->printInformationPercentageOfTotal(filesAndFoldersListPercentage);	

	return true;
}

qint64 FolderGrouping::getTotalSize(const QString& path) const noexcept
{
	auto totalSize = QFileInfo(path).size();

	QDir directory(path);

	for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden))
		(it.isDir() && !it.isSymLink()) ? totalSize += this->getTotalSize(it.absoluteFilePath()) : totalSize += it.size();

	return totalSize;
}

QMap<QString, qint64> FolderGrouping::getFilesAndFolders(const QString& path) const noexcept
{
	QMap<QString, qint64> filesAndFoldersList;

	for (const auto& it : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden))
	{
		const auto absolutePath = it.absoluteFilePath();
		filesAndFoldersList.insert(absolutePath, this->getTotalSize(absolutePath));
	}

	return filesAndFoldersList;
}

QMap<QString, double> FolderGrouping::getInformationPercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList) const noexcept
{
	QMap<QString, double> filesAndFoldersListPercentage;

	for (auto it = filesAndFoldersList.begin(); it != filesAndFoldersList.end(); ++it)
	{
		const auto percentageOfTotal = double(it.value() * 100) / totalSize;
		filesAndFoldersListPercentage.insert(it.key(), percentageOfTotal);
	}

	return filesAndFoldersListPercentage;
}

void FolderGrouping::printInformationPercentageOfTotal(const QMap<QString, double>& filesAndFoldersList) const noexcept
{
	QTextStream cout(stdout);

	for (auto it = filesAndFoldersList.begin(); it != filesAndFoldersList.end(); ++it)
		cout << it.key() << " " << it.value() << "%" << endl;
}
