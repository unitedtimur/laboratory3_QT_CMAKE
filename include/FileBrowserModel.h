#pragma once

#include <QAbstractTableModel>
#include <QList>
#include "include/Data.h"

class FileBrowserModel final : public QAbstractTableModel
{
	Q_OBJECT 

public:
	explicit FileBrowserModel(QObject* parent = nullptr, const QList<Data>& data = QList<Data>());
	~FileBrowserModel() = default;


private:
	QList<Data> _data;

	// Унаследовано через QAbstractTableModel
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setData(const QList<Data>& data);
	bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex());
};