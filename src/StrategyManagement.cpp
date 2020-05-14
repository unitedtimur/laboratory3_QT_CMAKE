#include "include/StrategyManagement.h"
#include "include/AbstractStrategy.h"

// Производим инициализацию
StrategyManagement::StrategyManagement(AbstractStrategy* strategy) : 
	_strategy(strategy)
{
}

// Удаляем объект
StrategyManagement::~StrategyManagement()
{
	delete this->_strategy;
}

// Удаляем объект и выставляем новый
void StrategyManagement::setStrategy(AbstractStrategy* strategy)
{
	delete this->_strategy;
	_strategy = strategy;
}

// Выполняем функцию для стратегии с передаваемым аргументом ( explorer() )
void StrategyManagement::doIt(const QString& path)
{
	_strategy->explorer(path);
}
