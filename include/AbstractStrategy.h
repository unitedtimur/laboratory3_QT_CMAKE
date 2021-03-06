﻿#pragma once

#include <QString>
#include "include/Data.h"

// Интерфейс стратегии объявляет операции, общие для всех поддерживаемых версий заданного алгоритма
// StrategyManager использует этот интерфейс для вызова алгоритма, определённого конкретными стратегиями
class AbstractStrategy
{
public:
    explicit AbstractStrategy() = default;
    virtual ~AbstractStrategy() = default;
    virtual bool explorer(const QString& path, QList<Data>& data) = 0;
};