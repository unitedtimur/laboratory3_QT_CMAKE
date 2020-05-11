#pragma once

#include "include/AbstractStrategy.h"

class FolderGrouping final : public AbstractStrategy
{
public:
	explicit FolderGrouping() = default;
	virtual ~FolderGrouping() override = default;
	bool explorer(const QString& path) override;

private:
	QMap<QString, qint64> getFilesAndFolders(const QString& path) const noexcept;
	QMap<QString, double> getInformationByFoldersPercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList) const noexcept;
};