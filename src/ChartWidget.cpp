#include "include/ChartWidget.h"
#include <QChart>
#include <QFileInfo>
#include <QBarSeries>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>
#include <QStackedBarSeries>

using namespace QtCharts;

ChartWidget::ChartWidget(QWidget* parent, const QList<Data>& data) : 
	QWidget(parent),
	_data(data)
{
	this->convertData();
}

QChart* ChartWidget::dataBarChart()
{
	const auto chart = new QChart;
	const auto series = new QBarSeries;

	for (const auto& it : _data)
	{
		const auto label = it._name + " - (" + QString::number(it._percentage.toDouble(), 'g', 3) + ")%";
		const auto set = new QBarSet(label);
		set->append(it._percentage.toDouble());
		series->append(set);
	}

	chart->addSeries(series);
	chart->setTheme(QChart::ChartTheme::ChartThemeQt);
	chart->legend()->setAlignment(Qt::AlignRight);

	return chart;
}

QtCharts::QChart* ChartWidget::dataPieChart()
{
	const auto chart = new QChart;
	const auto series = new QPieSeries;

	for (const auto& it : _data)
	{
		const auto label = it._name + " - (" + QString::number(it._percentage.toDouble(), 'g', 3) + ")%";
		const auto value = it._percentage.toDouble();
		const auto slice = new QPieSlice(label, value);
		series->append(slice);
	}

	chart->addSeries(series);
	chart->setTheme(QChart::ChartTheme::ChartThemeQt);
	chart->legend()->setAlignment(Qt::AlignRight);

	return chart;
}

QtCharts::QChart* ChartWidget::dataStackedBarChart()
{
	const auto chart = new QChart;
	const auto series = new QStackedBarSeries;

	for (const auto& it : _data)
	{
		const auto label = it._name + " - (" + QString::number(it._percentage.toDouble(), 'g', 3) + ")%";
		const auto set = new QBarSet(label);
		set->append(it._percentage.toDouble());
		series->append(set);
	}

	chart->addSeries(series);
	chart->setTheme(QChart::ChartTheme::ChartThemeQt);
	chart->legend()->setAlignment(Qt::AlignRight);

	return chart;
}

void ChartWidget::convertData()
{
	QMap<QString, Data> sorting;

	// Группировка данных Data для правильного отображение диаграммы поля ' Others '
	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		// Формирование блока Others для диаграмм
		if (it->_size.toDouble() >= 0 && it->_percentage.toDouble() < 0.01)
		{
			const auto others = QString("Others");
			const auto size = sorting.value(others)._size.toDouble() + it->_size.toDouble();
			const auto percentage = sorting.value(others)._percentage.toDouble() + it->_percentage.toDouble();
			sorting.insert(others, Data(others, QString::number(size, 'g', 2), QString::number(percentage, 'g', 2)));
		}
		// Формирование обычного блока диаграммы
		else
		{
			const auto name = it->_name.split("/").last();
			sorting.insert(name, Data(name, it->_size, it->_percentage));
		}
	}

	_data.clear();

	for (const auto& it : sorting.keys())
	{
		const auto value = sorting.value(it);
		_data.push_back(Data(value._name, value._size, value._percentage));
	}
}
