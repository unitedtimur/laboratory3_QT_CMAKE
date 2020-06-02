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

	using namespace QtCharts;

    QtCharts::QChartView* chartView;
	QtCharts::QBarSet* set = new QtCharts::QBarSet("SALAM");
	set->append({ 1, 2, 3, 4 });

	QBarSeries* series = new QBarSeries;
	series->append(set);

	QChart* chart = new QChart;
	chart->addSeries(series);

	chartView = new QChartView(chart);
	//ui->chartLayout->addWidget(chartView);
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
		auto chart = new QChart;
		auto series = new QBarSeries;

		for (const auto& it : _data)
		{
			auto barSet = new QBarSet((QFileInfo(it._name).suffix().isEmpty() ? "Unknown" : QFileInfo(it._name).suffix()) + ' ' + it._percentage + " %");
			barSet->append(it._percentage.toDouble());
			series->append(barSet);
		}

		chart->addSeries(series);
		auto chartView = new QChartView(chart);
		
		QLayoutItem* item;
		ui->chartLayout->takeAt(0);

		while ((item = ui->chartLayout->takeAt(0)) != NULL)
		{
			delete item->widget();
			delete item;
		}


		ui->chartLayout->addWidget(chartView);

		break;
	}
	case Explorer::ConditionDisplayed::byPie:
		break;
	default:
		break;
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
}

void Explorer::selectionDisplaying(const qint32& index)
{
	switch (index)
	{
	case 0x00:	_conditionDisplayed = ConditionDisplayed::byBar; break;
	case 0x01:	_conditionDisplayed = ConditionDisplayed::byPie; break;
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
