#include "include/TypeGrouping.h"
#include "include/Configuration.h"
#include <qdebug.h>

bool TypeGrouping::explorer(const QString& path)
{
	QFileInfo file(path);

	if (!file.exists() && !file.isReadable())
		return false;

	const auto absolutePath = file.absoluteFilePath();
	const auto totalSize = Configuration::GetTotalSize(absolutePath);
	const auto filesAndFoldersList = this->getAllFiles(absolutePath);
	const auto filesAndFoldersListPercentage = this->getInformationByTypePercentageOfTotal(totalSize, filesAndFoldersList);
	Configuration::PrintInformationPercentageOfTotal(filesAndFoldersListPercentage);

	return true;
}

void TypeGrouping::setMap(const QMap<QString, qint64>& from, QMap<QString, qint64>& to) noexcept
{
	for (auto it = from.begin(); it != from.end(); ++it)
		to.insert(it.key(), it.value());
}

QMap<QString, qint64> TypeGrouping::getAllFiles(const QString& path) noexcept
{
	QMap<QString, qint64> fileList;

	for (const auto& it : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
		(it.isDir() && !it.isSymLink()) ? this->setMap(this->getAllFiles(it.absoluteFilePath()), fileList) : fileList.insert(it.absoluteFilePath(), it.size());
	
	return fileList;
}

QMap<QString, double> TypeGrouping::getInformationByTypePercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList) const noexcept
{
	QMap<QString, double> filesAndFoldersListPercentage;

	for (auto it = filesAndFoldersList.begin(); it != filesAndFoldersList.end(); ++it)
	{
		const auto percentageOfTotal = double(it.value() * 100) / totalSize;
		auto suffix = QFileInfo(it.key()).suffix();
		if (suffix.isEmpty())
			suffix = "unknown";
		filesAndFoldersListPercentage.insert(suffix, filesAndFoldersListPercentage[suffix] + percentageOfTotal);
	}

	return filesAndFoldersListPercentage;
}
