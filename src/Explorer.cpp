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
	
	// Задаём минимальный размер окна приложения
	this->setMinimumSize(1200, 600);
	
	// Вызываем метод, инициализирующий views
	this->initModelDir();

	// Сигнал выбора группировки 
	connect(ui->groupedBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::selectionGrouping);
	//Сигнал выбора способа отображения
	connect(ui->displayBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::selectionDisplaying);
	//Сигнал выбора файлов в дереве слева 
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
	// Выставление модели для дерева слева фильтров
	_modelDir->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	// Выставление корня для модели слева
	_modelDir->setRootPath(QDir::currentPath());
	// Устанавливаем модель в QTreeView
	ui->treeView->setModel(_modelDir);
	// Говорим QTreeView отображать текст в независимости от размеров окна
	ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// Говори QTableView отображать на всю ширину и высоту окна
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	// Смягчаем отрисовку диаграмм
	ui->chartView->setRenderHint(QPainter::Antialiasing);
}

void Explorer::setTableModel(QAbstractTableModel* model)
{
	// Устанавливаем передаваемую модель в QTableView
	ui->tableView->setModel(model);
}

void Explorer::expectAndDisplayTableModel()
{
	// Проверяем, не пуст ли путь в дереве
	if (_currentPath.isEmpty())
		return;

	switch (_conditionGrouped)
	{
		// Если выбрана группировка по группам
	case Explorer::ConditionGrouped::byFolders:
	{
		// Устанавливаем стратегию по папкам
		_strategyManagement->setStrategy(new FolderGrouping);
		// Передаём путь и лист данных, который должен быть заполнен
		_strategyManagement->doIt(_currentPath, _data);
		// Устанавливаем модель данных
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		// Проверяем не пусты ли данные
		if (_data.isEmpty()) return;
		// Устанавливаем модель в QTableView
		this->setTableModel(fileBrowserModel);
		break;
	}
	case Explorer::ConditionGrouped::byTypes:
	{
		// Аналогично для группировки по типам
		_strategyManagement->setStrategy(new TypeGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		if (_data.isEmpty()) return;
		this->setTableModel(fileBrowserModel);
		break;
	}
	default:
	{
		// На невозможный случай, если будет добавлено значение в QComboBox, но обработки не будет
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
	// Если выбрано отображение в виде Bar диаграммы
	case Explorer::ConditionDisplayed::byBar:
	{
		// Проверяем не пуст ли данные
		if (_data.isEmpty()) return;
		// Вызываем Bar chart для переданных данных и устанавливаем в QChartView
		ui->chartView->setChart(ChartWidget(this, _data).dataBarChart());
		break;
	}
	// Аналогично для Pie диаграммы
	case Explorer::ConditionDisplayed::byPie:
	{
		if (_data.isEmpty()) return;
		ui->chartView->setChart(ChartWidget(this, _data).dataPieChart());
		break;
	}
	// Аналогично для Stacked Bar диаграммы 
	case Explorer::ConditionDisplayed::byStackedBar:
	{
		if (_data.isEmpty()) return;
		ui->chartView->setChart(ChartWidget(this, _data).dataStackedBarChart());
		break;
	}
	// На невозможный случай, если будут добавлены необратонные значения в QComboBox
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
	// Если пользователь нажал выбрать группировку выставляются соответствующие флаги
	switch (index)
	{
	case 0x00:	_conditionGrouped = ConditionGrouped::byFolders; break;
	case 0x01:	_conditionGrouped = ConditionGrouped::byTypes; break;
	default:	_conditionGrouped = ConditionGrouped::byFolders; break;
	}
	// После выставленных флагов производится отображение модели в QTableView и отображение диаграмм
	this->expectAndDisplayTableModel();
	this->expectAndDisplayChartWidget();
}

void Explorer::selectionDisplaying(const qint32& index)
{
	// Если пользователь выбрал выбор отображения диаграмм
	switch (index)
	{
	case 0x00:	_conditionDisplayed = ConditionDisplayed::byBar; break;
	case 0x01:	_conditionDisplayed = ConditionDisplayed::byPie; break;
	case 0x02:	_conditionDisplayed = ConditionDisplayed::byStackedBar; break;
	default:	_conditionDisplayed = ConditionDisplayed::byBar; break;
	}
	// Вызывается метод отрисовки диаграммы
	this->expectAndDisplayChartWidget();
}

void Explorer::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	Q_UNUSED(deselected);
	// Для QTreeView сигнала нажатия (раскрытия) области сохраняем индексы
	const auto indexes = selected.indexes();
	// Сохраняем выбранный путь в выбранной модели данных
	const auto pathToDir = _modelDir->filePath(indexes[0]);
	// Сохраняем этот путь
	_currentPath = pathToDir;
	// Вызываем методы построения модели для отображения в QTableView и отрисовку диаграмм
	this->expectAndDisplayTableModel();
	this->expectAndDisplayChartWidget();
}
