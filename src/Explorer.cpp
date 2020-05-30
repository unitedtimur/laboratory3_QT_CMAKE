#include "include/Explorer.h"
#include "ui_Explorer.h"

#include <QFileSystemModel>
#include <QItemSelectionModel>

Explorer::Explorer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Explorer), 
	_modelDir(new QFileSystemModel(this))
{
	ui->setupUi(this);

	this->setMinimumSize(1200, 600);
	this->initModelDir();

	connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Explorer::selectionChanged);
}

Explorer::~Explorer()
{
	delete ui;
	delete _modelDir;
}

void Explorer::initModelDir()
{
	_modelDir->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	_modelDir->setRootPath(QDir::currentPath());
	ui->treeView->setModel(_modelDir);
}

void Explorer::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	Q_UNUSED(deselected);

	QModelIndexList indexes = selected.indexes();

	//for (const auto& index : indexes)

}
