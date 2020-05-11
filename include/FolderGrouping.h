#pragma once

#include "include/AbstractStrategy.h"

class FolderGrouping final : public AbstractStrategy
{
public:
	explicit FolderGrouping() = default;
	virtual ~FolderGrouping() override = default;
	bool explorer(const QString& path) override;

private:
	qint64 getTotalSize(const QString& path) const noexcept;
	QMap<QString, qint64> getFilesAndFolders(const QString& path) const noexcept;
	QMap<QString, double> getInformationPercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList) const noexcept;
	void printInformationPercentageOfTotal(const QMap<QString, double>& filesAndFoldersList) const noexcept;
};