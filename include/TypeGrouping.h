#pragma once

#include "include/AbstractStrategy.h"

// Класс стратегии для группировки по типам
class TypeGrouping : public AbstractStrategy
{
public:
	// Дефолтный конструктор и деструктор
	explicit TypeGrouping() = default;
	virtual ~TypeGrouping() override = default;
	// Основная доступная функция
	bool explorer(const QString& path, QList<Data>& data) override;

protected:
	// Функция копирования QMap
	void setMap(const QMap<QString, qint64>& from, QMap<QString, qint64>& to) noexcept;
	// Функция возвращает все файлы
	QMap<QString, qint64> getAllFiles(const QString& path) noexcept;
	// Функция возвращает информацию о типах в процентном соотношении от общего размера
	QMap<QString, double> getInformationByTypePercentageOfTotal(const qint64& totalSize, const QMap<QString, qint64>& filesAndFoldersList, QList<Data>& data) const noexcept;
};