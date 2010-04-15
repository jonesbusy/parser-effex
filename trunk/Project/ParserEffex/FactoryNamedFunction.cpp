#include "FactoryNamedFunction.h"

FactoryNamedFunction::FactoryNamedFunction()
{
    // Trigonometriques
    functions["sin"] = sin;
    functions["cos"] = cos;
    functions["tan"] = tan;
    functions["asin"] = asin;
    functions["acos"] = acos;
    functions["atan"] = atan;

    // Hyperboliques
    functions["sinh"] = sinh;
    functions["cosh"] = cosh;
    functions["tanh"] = tanh;


    // Exponentielles et logarithmes
    functions["exp"] = exp;
    functions["log"] = log10;
    functions["ln"] = log;

    // Racine
    functions["sqrt"] = sqrt;

    // Valeur absolue
    functions["abs"] = fabs;


}

FactoryNamedFunction::~FactoryNamedFunction()
{
    functions.clear();
}

NamedFunction* FactoryNamedFunction::getInstance(std::string name) const
{
    // Chercher la fonction
    std::map<std::string, double(*)(double)>::const_iterator search;
    search = functions.find(name);

    if (search != functions.end())
        return new NamedFunction(name, search->second);

    else
        return NULL;

}
