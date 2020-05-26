#include "include/Explorer.h"
#include "ui_Explorer.h"

#include <QFileSystemModel>

Explorer::Explorer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Explorer), 
	_modelDir(new QFileSystemModel(this))
{
	ui->setupUi(this);

	this->setMinimumSize(1200, 600);
	this->initModelDir();
	_modelDir->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	_modelDir->setRootPath(QDir::currentPath());
	ui->treeView->setModel(_modelDir);


	//const auto modelFile = new QFileSystemModel(this);
	//modelFile->setFilter(QDir::Files | QDir::NoDotAndDotDot);
	//modelFile->setRootPath(QDir::currentPath());

}

Explorer::~Explorer()
{
	delete ui;
	delete _modelDir;
}

void Explorer::initModelDir()
{
	
}
