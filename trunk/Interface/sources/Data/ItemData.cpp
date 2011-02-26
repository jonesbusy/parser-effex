#include "Data/ItemData.h"

ItemData::ItemData(const QString& name, const QString& domain, double value) : name(name), domain(domain), value(value)
{
}

const QString& ItemData::getName() const
{
    return this->name;
}

const QString& ItemData::getDomain() const
{
    return this->domain;
}

double ItemData::getValue() const
{
    return this->value;
}
