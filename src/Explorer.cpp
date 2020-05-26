#include "include/Explorer.h"
#include "ui_Explorer.h"

Explorer::Explorer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Explorer)
{
	ui->setupUi(this);
}

Explorer::~Explorer()
{
	delete ui;
}
