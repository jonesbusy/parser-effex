#include "AbstractFunction.h"

AbstractFunction::AbstractFunction(char variable) : VAR(variable)
{

}

AbstractFunction::~AbstractFunction()
{

}

AbstractFunction::operator double() const
{
    return eval(AbstractFunction::defaultValue);
}


void AbstractFunction::setEval(double value)
{
    AbstractFunction::defaultValue = AbstractFunction::defaultValue = value;
}

double AbstractFunction::defaultValue = 10;
