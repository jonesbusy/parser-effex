#include "Data/MathTools.h"

bool MathTools::isNaN(double value)
{
    return value != value;
}

bool MathTools::isInfinity(double value)
{
    return (value == NINF || value == PINF);
}

bool MathTools::differentSign(IExpression* function, double x1, double x2, double delta)
{
    double y1 = function->eval(x1);
    double y2 = function->eval(x2);

    return (y1 > 0 && y2 < 0) || (y1 < 0 && y2 > 0);
}

void MathTools::reverse(double& x1, double& x2)
{
    double temp = x1;

    x1 = x2;
    x2 = temp;
}

double MathTools::integral(IExpression* function, double x1, double x2, int steps)
{
    // Surface
    double surface = 0;

    // Largeur de chaque trapèze
    double fragment = (x2 - x1) / steps;

    // Décalage courant
    double shift = 0;

    // Somme de chaque trapèze
    for (register int i = 0; i < steps; i++)
    {
        surface += fragment * ((fabs(function->eval(x1 + shift)) + fabs(function->eval(x1 + shift + fragment))) / 2);

        shift += fragment;
    }

    return fabs(surface);
}

double MathTools::tangent(IExpression* function, double x1, double delta)
{
    double x2 = x1 + delta;

    double y1 = function->eval(x1);
    double y2 = function->eval(x2);

    // DeltaY / DeltaX
    return (y2 - y1) / (x2 - x1);
}

double MathTools::zero(IExpression* function, double x1, double x2, bool* found, double delta)
{
    // Inverser les valeurs si besoin
    if (x1 > x2)

        MathTools::reverse(x1, x2);

    // Passer en un zéro négatif
    if (x1 == 0)

        x1 -= delta;

    // Pas trouvé (pour l'instant)
    if (found != NULL)

        *found = false;

    // N'encadre pas le zéro
    if (MathTools::differentSign(function, x1, x2))
    {
        // Milieu de l'intervalle
        double middle;

        while (fabs(x1 - x2) > delta)
        {
            middle = (x1 + x2) / 2;

            // Partie gauche inutile
            if (function->eval(x1) * function->eval(middle) > 0)

                x1 = middle;

            // Partie droite inutile
            else

                x2 = middle;
        }

        if (MathTools::isNaN(function->eval(x2)))

            return NaN;

        if (found != NULL)

            *found = true;

        return x2;
    }

    return NaN;
}

double MathTools::maximum(IExpression* function, double x1, double x2, double delta)
{
    // Inverser les valeurs si besoin
    if (x1 > x2)

        MathTools::reverse(x1, x2);

    double xMax = x1;

    double yMax = function->eval(xMax);

    for (register double x = x1 + delta; x <= x2; x += delta)
    {
        double y = function->eval(x);

        if (!MathTools::isNaN(y) && (y > yMax || MathTools::isNaN(yMax)))
        {
            xMax = x;
            yMax = y;
        }
    }

    return xMax;
}

double MathTools::minimum(IExpression* function, double x1, double x2, double delta)
{
    // Inverser les valeurs si besoin
    if (x1 > x2)

        MathTools::reverse(x1, x2);

    double xMin = x1;

    double yMin = function->eval(xMin);

    for (register double x = x1 + delta; x <= x2; x += delta)
    {
        double y = function->eval(x);

        if (!MathTools::isNaN(y) && (y < yMin || MathTools::isNaN(yMin)))
        {
            xMin = x;
            yMin = y;
        }
    }

    return xMin;
}

double MathTools::setDecimal(double value, int decimal)
{
    // Non traitable ?
    if (MathTools::isNaN(value) || MathTools::isInfinity(value))

        return value;

    int shift = (int)pow(10, decimal);

    // Déplacement à gauche, troncation, puis déplacement à droite
    value *= shift;
    value = floor(value);
    value /= shift;

    return value;
}
