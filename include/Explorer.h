#pragma once

#include <QWidget>
#include <QItemSelection>

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

	Q_SLOT void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
	Ui::Explorer* ui;
	QFileSystemModel* _modelDir;
};