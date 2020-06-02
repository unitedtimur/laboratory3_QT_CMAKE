#include "include/Explorer.h"
#include "ui_Explorer.h"

#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QAbstractTableModel>
#include "include/StrategyManagement.h"
#include "include/FolderGrouping.h"
#include "include/TypeGrouping.h"
#include "include/FileBrowserModel.h"
#include <QDebug>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include "include/ChartWidget.h"

Explorer::Explorer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Explorer),
	_modelDir(new QFileSystemModel(this)),
	_strategyManagement(new StrategyManagement(new FolderGrouping)),
	_conditionGrouped(ConditionGrouped::byFolders),
	_conditionDisplayed(ConditionDisplayed::byBar)
{
	ui->setupUi(this);
	this->setMinimumSize(1200, 600);
	this->initModelDir();

	connect(ui->groupedBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::selectionGrouping);
	connect(ui->displayBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::selectionDisplaying);
	connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Explorer::selectionChanged);
}

Explorer::~Explorer()
{
	delete _strategyManagement;
	delete _modelDir;
	delete ui;
}

void Explorer::initModelDir()
{
	_modelDir->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	_modelDir->setRootPath(QDir::currentPath());
	ui->treeView->setModel(_modelDir);
	ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->chartView->setRenderHint(QPainter::Antialiasing);
}

void Explorer::setTableModel(QAbstractTableModel* model)
{
	ui->tableView->setModel(model);
}

void Explorer::expectAndDisplayTableModel()
{
	if (_currentPath.isEmpty())
		return;

	switch (_conditionGrouped)
	{
	case Explorer::ConditionGrouped::byFolders:
	{
		_strategyManagement->setStrategy(new FolderGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		if (_data.isEmpty()) return;
		this->setTableModel(fileBrowserModel);
		break;
	}
	case Explorer::ConditionGrouped::byTypes:
	{
		_strategyManagement->setStrategy(new TypeGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		if (_data.isEmpty()) return;
		this->setTableModel(fileBrowserModel);
		break;
	}
	default:
	{
		_strategyManagement->setStrategy(new FolderGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		if (_data.isEmpty()) return;
		this->setTableModel(fileBrowserModel);
		break;
	}
	}
}

void Explorer::expectAndDisplayChartWidget()
{
	using namespace QtCharts;

	if (_currentPath.isEmpty())
		return;

	switch (_conditionDisplayed)
	{
	case Explorer::ConditionDisplayed::byBar:
	{
		if (_data.isEmpty()) return;
		ui->chartView->setChart(ChartWidget(this, _data).dataBarChart());
		break;
	}
	case Explorer::ConditionDisplayed::byPie:
	{
		if (_data.isEmpty()) return;
		ui->chartView->setChart(ChartWidget(this, _data).dataPieChart());
		break;
	}
	case Explorer::ConditionDisplayed::byStackedBar:
	{
		if (_data.isEmpty()) return;
		ui->chartView->setChart(ChartWidget(this, _data).dataStackedBarChart());
		break;
	}
	default:
	{
		if (_data.isEmpty()) return;
		ui->chartView->setChart(ChartWidget(this, _data).dataBarChart());
		break;
	}
	}
}

void Explorer::selectionGrouping(const qint32& index)
{
	switch (index)
	{
	case 0x00:	_conditionGrouped = ConditionGrouped::byFolders; break;
	case 0x01:	_conditionGrouped = ConditionGrouped::byTypes; break;
	default:	_conditionGrouped = ConditionGrouped::byFolders; break;
	}
	this->expectAndDisplayTableModel();
	this->expectAndDisplayChartWidget();
}

void Explorer::selectionDisplaying(const qint32& index)
{
	switch (index)
	{
	case 0x00:	_conditionDisplayed = ConditionDisplayed::byBar; break;
	case 0x01:	_conditionDisplayed = ConditionDisplayed::byPie; break;
	case 0x02:	_conditionDisplayed = ConditionDisplayed::byStackedBar; break;
	default:	_conditionDisplayed = ConditionDisplayed::byBar; break;
	}
	this->expectAndDisplayChartWidget();
}

void Explorer::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	Q_UNUSED(deselected);
	const auto indexes = selected.indexes();
	const auto pathToDir = _modelDir->filePath(indexes[0]);
	
	_currentPath = pathToDir;

	this->expectAndDisplayTableModel();
	this->expectAndDisplayChartWidget();
}
