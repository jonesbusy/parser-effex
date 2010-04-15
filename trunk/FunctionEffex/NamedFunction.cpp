#include "NamedFunction.h"

NamedFunction::NamedFunction(std::string name, double(*function)(double))
    : name(name), function(function)
{

}

double NamedFunction::eval(double value) const
{
    return function(value);
}

double NamedFunction::operator()(double value) const
{
    return eval(value);
}
