#pragma once

#include <QWidget>
#include <QItemSelection>
#include "include/Data.h"

namespace Ui
{
	class Explorer;
}

class QFileSystemModel;
class StrategyManagement;
class QAbstractTableModel;

class Explorer : public QWidget
{
	Q_OBJECT

public:
	explicit Explorer(QWidget* parent = nullptr);
	~Explorer();

protected:
	enum class ConditionGrouped
	{
		byFolders	= 0x01,
		byTypes		= 0x02
	};

	enum class ConditionDisplayed
	{
		byBar		= 0x01,
		byPie		= 0x02
	};

	void initModelDir();
	void setTableModel(QAbstractTableModel* model);
	void expectAndDisplayTableModel();
	void expectAndDisplayChartWidget();

	Q_SLOT void selectionGrouping(const qint32& index);
	Q_SLOT void selectionDisplaying(const qint32& index);
	Q_SLOT void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
	Ui::Explorer*		ui;
	QFileSystemModel*	_modelDir;
	StrategyManagement* _strategyManagement;
	ConditionGrouped	_conditionGrouped;
	ConditionDisplayed	_conditionDisplayed;
	QList<Data>			_data;
	QString				_currentPath;
};