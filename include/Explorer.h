#pragma once

#include <QWidget>

namespace Ui
{
	class Explorer;
}

class QFileSystemModel;

class Explorer : public QWidget
{
	Q_OBJECT

public:
	explicit Explorer(QWidget* parent = nullptr);
	~Explorer();

protected:
	void initModelDir();

private:
	Ui::Explorer* ui;
	QFileSystemModel* _modelDir;
};