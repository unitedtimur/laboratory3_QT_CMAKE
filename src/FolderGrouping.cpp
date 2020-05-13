#include "include/FolderGrouping.h"
#include "include/Configuration.h"

bool FolderGrouping::explorer(const QString& path)
{
	QFileInfo file(path);

	if (!file.exists() && !file.isReadable())
		return false;

	const auto absolutePath = file.absoluteFilePath();
	const auto totalSize = Configuration::GetTotalSize(absolutePath);
	const auto filesAndFoldersList = this->getFilesAndFolders(absolutePath);
	const auto filesAndFoldersListPercentage = this->getInformationByFoldersPercentageOfTotal(totalSize, filesAndFoldersList);
	Configuration::PrintInformationPercentageOfTotal(filesAndFoldersListPercentage);

	return true;
}

QMap<QString, double> FolderGrouping::getFilesAndFolders(const QString& path) const noexcept
{
	QMap<QString, double> filesAndFoldersList;

	if (QFileInfo(path).isDir())
	{
		for (const auto& it : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::AllEntries, QDir::Name | QDir::Type))
		{
			const auto absolutePath = it.absoluteFilePath();
			filesAndFoldersList.insert(absolutePath, Configuration::GetTotalSize(absolutePath));
		}
	}
	else
		filesAndFoldersList.insert(path, QFileInfo(path).size());

	return filesAndFoldersList;
}

QMap<QString, double> FolderGrouping::getInformationByFoldersPercentageOfTotal(const qint64& totalSize, const QMap<QString, double>& filesAndFoldersList) const noexcept
{
	QMap<QString, double> filesAndFoldersListPercentage;

	for (auto it = filesAndFoldersList.begin(); it != filesAndFoldersList.end(); ++it)
	{
		const auto percentageOfTotal = double(it.value() * 100) / totalSize;
		filesAndFoldersListPercentage.insert(it.key(), percentageOfTotal);
	}

	return filesAndFoldersListPercentage;
}


