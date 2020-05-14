#pragma once

#include "include/AbstractStrategy.h"

class TypeGrouping : public AbstractStrategy
{
public:
	explicit TypeGrouping() = default;
	virtual ~TypeGrouping() override = default;
	bool explorer(const QString& path) override;

protected:
	void setMap(const QMap<QString, qint64>& from, QMap<QString, qint64>& to) noexcept;
	QMap<QString, qint64> getAllFiles(const QString& path) noexcept;
	QMap<QString, double> getInformationByTypePercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList) const noexcept;
};