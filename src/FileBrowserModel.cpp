#include "include/FileBrowserModel.h"
#include "include/Configuration.h"

FileBrowserModel::FileBrowserModel(QObject* parent, const QList<Data>& data) :
	QAbstractTableModel(parent),
	_data(data)
{
}

int FileBrowserModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return _data.count();
}

int FileBrowserModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return Configuration::NUMBER_OF_COLUMNS;
}

QVariant FileBrowserModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || _data.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
		return QVariant();

	switch (index.column())
	{
		case 0x00: return _data[index.row()]._name;
		case 0x01: return _data[index.row()]._size;
		case 0x02: return _data[index.row()]._percentage;
		default: return QVariant();
	}
}

void FileBrowserModel::setData(const QList<Data>& data)
{
	_data = data;
}

bool FileBrowserModel::insertRows(int position, int rows, const QModelIndex& index)
{
	

	return true;
}
