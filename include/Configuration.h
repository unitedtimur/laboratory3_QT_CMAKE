#pragma once

#include <QDir>
#include <QMap>
#include <QTextStream>

namespace Configuration
{
	inline static qint64 GetTotalSize(const QString& path)
	{
		auto totalSize = 0;

		QDir directory(path);

		for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
			(it.isDir() && !it.isSymLink()) ? totalSize += GetTotalSize(it.absoluteFilePath()) : totalSize += it.size();

		return totalSize;
	}

	inline static void PrintInformationPercentageOfTotal(const QMap<QString, double>& filesAndFoldersList)
	{
		QTextStream cout(stdout);

		for (auto it = filesAndFoldersList.begin(); it != filesAndFoldersList.end(); ++it)
			cout << it.key() << " " << it.value() << "%" << endl;
	}
}