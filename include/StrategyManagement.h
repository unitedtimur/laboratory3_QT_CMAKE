#pragma once

#include <QString>

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
	void doIt(const QString& path);

private:
	// Поле интерфейса стратегии
	class AbstractStrategy* _strategy;
};