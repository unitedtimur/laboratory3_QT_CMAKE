#pragma once

#include <QObject>

/*
** Forward declaration
*/
class QDir;

class Explorer : public QObject
{
	Q_OBJECT
public:
	explicit Explorer();
	~Explorer();

	Q_SLOT void bypass(const QString& name) noexcept;

private:
	QDir* dir;
};