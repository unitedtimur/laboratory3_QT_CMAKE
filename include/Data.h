#pragma once

// Структура данных, хранящая имя, размер, и процентное соотношение
struct Data
{
	explicit Data(const QString& name = "", const QString& size = "", const QString& percentage = "") : _name(name), _size(size), _percentage(percentage) {}
	QString _name, _size, _percentage;
};