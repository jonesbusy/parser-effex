#include <iostream>
#include <cstdlib>

#include "IExpression.h"
#include "Parser.h"
#include "MathFunction.h"

using namespace std;

int main()
{

    Parser p("1/x");
    IExpression* expression = p.parse();

    double valeur;

    //double valeur = MathFunction::integral(expression, 0, 20, 1000);
    //valeur = MathFunction::maximum(expression, -2, 2);
    valeur = MathFunction::tangent(expression, 2);

    if(valeur == INFINITY)
        printf("inf");
    else
        printf("%.2f", valeur);

    return EXIT_SUCCESS;

}
