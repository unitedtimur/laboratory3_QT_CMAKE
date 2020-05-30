#include "include/FolderGrouping.h"
#include "include/Configuration.h"

bool FolderGrouping::explorer(const QString& path)
{
	// Открываем файл и проверяем, что он читабельный
	QFileInfo file(path);

	if (!file.exists() && !file.isReadable())
		return false;

	// Получаем абсолютный путь
	const auto absolutePath = file.absoluteFilePath();
	// Получаем полный размер в байтах папки / файла по переданному пути
	const auto totalSize = Configuration::GetTotalSize(absolutePath);
	// Получаем файлы и / или папки
	const auto filesAndFoldersList = this->getFilesAndFolders(absolutePath);
	// Получаем информацию о файлах и / или папках в процентном соотношении
	const auto filesAndFoldersListPercentage = this->getInformationByFoldersPercentageOfTotal(totalSize, filesAndFoldersList);
	// Выводим информацию
	if (filesAndFoldersListPercentage.empty())
		QTextStream(stdout) << "FolderGrouping: This path is empty" << endl;

	Configuration::PrintInformationPercentageOfTotal(filesAndFoldersListPercentage);

	return true;
}

QMap<QString, double> FolderGrouping::getFilesAndFolders(const QString& path) const noexcept
{
	QMap<QString, double> filesAndFoldersList;

	// Проходимся по всему подкаталогам в поисках файлов / папок и вычисляем размер
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

	// Проходимся по всем файлам / папкам и вычисляем размер в процентном соотношении от всего размера в байтах
	for (auto it = filesAndFoldersList.begin(); it != filesAndFoldersList.end(); ++it)
	{
		const auto percentageOfTotal = double(it.value() * 100) / totalSize;
		filesAndFoldersListPercentage.insert(it.key(), percentageOfTotal);
	}

	return filesAndFoldersListPercentage;
}


