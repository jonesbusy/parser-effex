#include "mathfunction.h"

double MathFunction::integral(IExpression* function, double x1, double x2, int steps)
{

}

double MathFunction::tangent(IExpression* function, double x1, double delta)
{
    double x2 = x1 + delta;
    double y1 = function->eval(x1);
    double y2 = function->eval(x2);

    // DeltaY / DeltaX
    return (y2 - y1)/(x2 - x1);
}

double MathFunction::zero(IExpression* function, double x1, double x2, double delta, bool* found)
{

    // Inverser les valeurs si besoin
    double tmp;
    if (x1 > x2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }

    // Passer en un zero negatif
    if(x1 == 0)
        x1 -= delta;

    // N'encadre pas le zero
    if(differentSign(function, x1, x2))
    {

        // Milieu de l'intervalle
        double middle;

        while (fabs(x1 - x2) > delta)
        {
            middle = (x1 + x2) / 2;

            // Partie gauche inutile
            if(function->eval(x1) * function->eval(middle) > 0)
                x1 = middle;

            // Partie droite inule
            else
                x2 = middle;

        }
        if(found != NULL)
            *found = false;
        return x2;
    }
    else
    {
        if(found != NULL)
            *found = false;
        return INFINITY;
    }
}

double MathFunction::maximum(IExpression* function, double x1, double x2, double delta)
{
    // Pour recuperer le max
    double max = function->eval(x1);

    // Pour calculer la nouvelle valeur
    double nextMax = 0;

    for(double i = x1 ; i <= x2 ; i+= delta)

        if ((nextMax = function->eval(i)) > max)
            max = nextMax;

    return max;
}

double MathFunction::minimum(IExpression* function, double x1, double x2, double delta)
{
    // Pour recuperer le min
    double min = function->eval(x1);

    // Pour calculer la nouvelle valeur
    double nextMin = 0;

    for(double i = x1 ; i <= x2 ; i+= delta)

        if ((nextMin = function->eval(i)) < min)
            min = nextMin;

    return min;
}

bool MathFunction::differentSign(IExpression* function, double x1, double x2, double delta)
{
    double y1 = function->eval(x1);
    double y2 = function->eval(x2);

    return (y1 > 0 && y2 < 0) || (y1 < 0 && y2 > 0);
}
