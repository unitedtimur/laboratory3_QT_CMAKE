#pragma once

#include <QString>
#include "include/Data.h"

// Управляющий класс, который предоставляет функционал для клиентов
class StrategyManagement
{
public:
	// Принимает в аргументе указатель на интерфейс стратегий
	explicit StrategyManagement(class AbstractStrategy* strategy = nullptr);
	// Деструктор
	~StrategyManagement();
	// Функция позволяет выставлять новую стратегию для объекта
	void setStrategy(class AbstractStrategy* strategy);
	// Функция бизнес-логики
	void doIt(const QString& path, QList<Data>& data);

private:
	// Поле интерфейса стратегии
	class AbstractStrategy* _strategy;
};