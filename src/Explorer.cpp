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

Explorer::Explorer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Explorer),
	_modelDir(new QFileSystemModel(this)),
	_strategyManagement(new StrategyManagement(new FolderGrouping)),
	_conditionGrouped(ConditionGrouped::byFolders)
{
	ui->setupUi(this);

	this->setMinimumSize(1200, 600);
	this->initModelDir();

	connect(ui->groupedBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::selectionGrouping);
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
	//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void Explorer::setTableModel(QAbstractTableModel* model)
{
	ui->tableView->setModel(model);
}

void Explorer::expectAndDisplayTableModel()
{
	switch (_conditionGrouped)
	{
	case Explorer::ConditionGrouped::byFolders:
	{
		_strategyManagement->setStrategy(new FolderGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		this->setTableModel(fileBrowserModel);
		break;
	}
	case Explorer::ConditionGrouped::byTypes:
	{
		_strategyManagement->setStrategy(new TypeGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		this->setTableModel(fileBrowserModel);
		break;
	}
	default:
	{
		_strategyManagement->setStrategy(new FolderGrouping);
		_strategyManagement->doIt(_currentPath, _data);
		const auto fileBrowserModel = new FileBrowserModel(nullptr, _data);
		this->setTableModel(fileBrowserModel);
		break;
	}
	}

	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

void Explorer::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	Q_UNUSED(deselected);
	const auto indexes = selected.indexes();
	const auto pathToDir = _modelDir->filePath(indexes[0]);
	_currentPath = pathToDir;
	this->expectAndDisplayTableModel();
}
