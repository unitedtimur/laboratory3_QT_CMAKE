#pragma once

#include <QString>

class AbstractStrategy
{
public:
    explicit AbstractStrategy() = default;
    virtual ~AbstractStrategy() = default;
    virtual void* explorer(const QString& path) = 0;
};