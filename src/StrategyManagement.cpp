#include "include/StrategyManagement.h"
#include "include/AbstractStrategy.h"

StrategyManagement::StrategyManagement(AbstractStrategy* strategy) : 
	_strategy(strategy)
{
}

StrategyManagement::~StrategyManagement()
{
	delete this->_strategy;
}

void StrategyManagement::setStrategy(AbstractStrategy* strategy)
{
	delete this->_strategy;
	_strategy = strategy;
}

void StrategyManagement::doIt(const QString& path)
{
	_strategy->explorer(path);
}
