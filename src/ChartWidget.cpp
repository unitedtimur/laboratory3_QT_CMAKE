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

// Метод для построения bar диаграммы
QChart* ChartWidget::dataBarChart()
{
	const auto chart = new QChart;
	const auto series = new QBarSeries;

	// Проходим по всем данным
	for (const auto& it : _data)
	{
		// Выбираем имена и процентное соотношение
		const auto label = it._name + " - (" + QString::number(it._percentage.toDouble(), 'g', 3) + ")%";
		// Создаём set
		const auto set = new QBarSet(label);
		// Заполняем значениями (процентными соотношениями)
		set->append(it._percentage.toDouble());
		// Добавляем в серию
		series->append(set);
	}

	// Добавляем серию в QChart
	chart->addSeries(series);
	// Выставляем тему 
	chart->setTheme(QChart::ChartTheme::ChartThemeQt);
	// Говорим отображать легенду справа
	chart->legend()->setAlignment(Qt::AlignRight);

	// Возвращаем QChart
	return chart;
}

// Аналогично как и bar chart (только здесь не set, а slice)
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

// Аналогично как и bar chart
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

	// Заполнение данных с сгруппированным блоком others
	for (const auto& it : sorting.keys())
	{
		const auto value = sorting.value(it);
		_data.push_back(Data(value._name, value._size, value._percentage));
	}
}
