/*******************************************************************
|
| File         : MathFunction.h
|
| Description  : Fourni differentes operation a effectuer
|                sur des fonctions
|
| Author       : Pascal Berberat
|                Valentin Delaye
|
| Created      : 21.04.2010
|
| Modified     : -
|
| C++ std      : math.h
|
| Dependencies : IExpression.h
|                libraire libFunctionEffex
|
|
| Version      : 1.0
|
*******************************************************************/

#ifndef MATHFUNCTION_H
#define MATHFUNCTION_H

#include <math.h>

#include "IExpression.h"

const double DELTA = 0.00001;

class MathFunction
{
        public:

        static double integral(IExpression* function, double x1, double x2, int steps = 1000);

        static double tangent(IExpression* function, double x, double delta = DELTA);

        static double zero(IExpression* function, double x1, double x2, double delta = DELTA, bool* found = NULL);

        static double maximum(IExpression* function, double x1, double x2, double delta = DELTA);

        static double minimum(IExpression* function, double x1, double x2, double delta = DELTA);

        static bool differentSign(IExpression* function, double x1, double x2, double delta = DELTA);
};

#endif // MATHFUNCTION_H
