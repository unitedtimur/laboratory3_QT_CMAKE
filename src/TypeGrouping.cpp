#include "include/TypeGrouping.h"
#include "include/Configuration.h"
#include <qdebug.h>

bool TypeGrouping::explorer(const QString& path)
{
	// Проверяем файл / папку на читабельность
	QFileInfo file(path);

	if (!file.exists() && !file.isReadable())
		return false;

	// Получаем абсолютный путь
	const auto absolutePath = file.absoluteFilePath();
	// Вычисляем полный размер по переданному пути
	const auto totalSize = Configuration::GetTotalSize(absolutePath);
	// Получаем список всех файлов
	const auto filesAndFoldersList = this->getAllFiles(absolutePath);
	// Получаем процентное соотношение типов относительно общего размера
	const auto filesAndFoldersListPercentage = this->getInformationByTypePercentageOfTotal(totalSize, filesAndFoldersList);
	// Выводим информацию
	Configuration::PrintInformationPercentageOfTotal(filesAndFoldersListPercentage);

	return true;
}

void TypeGrouping::setMap(const QMap<QString, qint64>& from, QMap<QString, qint64>& to) noexcept
{
	// Проходимся по всему from и вставляем его ключи / значения в to
	for (auto it = from.begin(); it != from.end(); ++it)
		to.insert(it.key(), it.value());
}

QMap<QString, qint64> TypeGrouping::getAllFiles(const QString& path) noexcept
{
	QMap<QString, qint64> fileList;

	// Проходимся по всем файлам и достаём размер файлов
	for (const auto& it : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
		(it.isDir() && !it.isSymLink()) ? this->setMap(this->getAllFiles(it.absoluteFilePath()), fileList) : fileList.insert(it.absoluteFilePath(), it.size());
	
	return fileList;
}

QMap<QString, double> TypeGrouping::getInformationByTypePercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList) const noexcept
{
	QMap<QString, double> filesAndFoldersListPercentage;

	// Проходимся по всем файлам, достаём суффикс типа и вычисляем его размер относительно всего общего размера
	// Стоит отметить, что в случае, если файл не имеет тип, то значение в QMap появится как unknown
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
