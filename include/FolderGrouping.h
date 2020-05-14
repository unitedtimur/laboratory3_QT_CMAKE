#pragma once

#include "include/AbstractStrategy.h"

// Класс стратегии для группировки по папкам
class FolderGrouping : public AbstractStrategy
{
public:
	// Дефолтный конструктор и деструктор
	explicit FolderGrouping() = default;
	virtual ~FolderGrouping() override = default;
	// Основная доступная функция
	bool explorer(const QString& path) override;

protected:
	// Функция возвращает переданные файлы или папки по переданному пути ( сгруппировав их )
	QMap<QString, double> getFilesAndFolders(const QString& path) const noexcept;
	// Функция возвращает информацию о файлах или папках, их размеры в процентах
	QMap<QString, double> getInformationByFoldersPercentageOfTotal(const qint64& totalSize, const QMap<QString, double>& filesAndFoldersList) const noexcept;
};