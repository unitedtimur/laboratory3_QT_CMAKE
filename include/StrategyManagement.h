#pragma once

#include <QString>

class StrategyManagement
{
public:
	explicit StrategyManagement(class AbstractStrategy* strategy = nullptr);
	~StrategyManagement();
	void setStrategy(class AbstractStrategy* strategy);
	void doIt(const QString& path);

private:
	class AbstractStrategy* _strategy;
};