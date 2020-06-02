#pragma once

#include <QWidget>
#include "include/Data.h"

namespace QtCharts
{
	class QChart;
}

// Класс занимающийся построением диаграмм
class ChartWidget final : public QWidget
{
	Q_OBJECT

public:
	explicit ChartWidget(QWidget* parent = nullptr, const QList<Data>& data = QList<Data>());
	~ChartWidget() = default;

	// Методы возвращающие диаграммы
	QtCharts::QChart* dataBarChart();
	QtCharts::QChart* dataPieChart();
	QtCharts::QChart* dataStackedBarChart();

protected:
	// Метод преобразования данных
	void convertData();

private:
	QList<Data> _data;
};