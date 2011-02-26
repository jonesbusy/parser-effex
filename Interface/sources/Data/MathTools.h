#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

/*!
 *  \file MathTools.h
 *  \author Pascal Berberat
 *  \author Valentin Delaye
 *  \date 12.04.2010
 *  \version 1.3
 */

#include <cmath>

#include "Expression/IExpression.h"

#define NaN (0.0 / 0.0)
#define PINF (1.0 / 0.0)
#define NINF (-1.0 / 0.0)

/*!
 *  \class MathTools
 *
 *  \brief La classe statique MathTools proposes des outils math�matiques.
 *
 *  Cette classe permet de calculer num�riquement des int�grales, des
 *  tangentes, des z�ros, des maximums ou des minimums. Elle propose aussi des
 *  m�thodes statiques pour d�tecter un NaN ou une infinit�e...
 */

class MathTools
{
    private:

    /*! Delta par d�faut */
    static const double DELTA = 0.0001;



    public:

    /*!
     *  D�termine si un nombre est de type "NaN".
     *
     *  \param value Nombre � tester
     *
     *  \return Vrai si le nombre est de type "NaN", sinon faux
     */
    static bool isNaN(double value);

    /*!
     *  D�termine si un nombre est +/- infini.
     *
     *  \param value Nombre � tester
     *
     *  \return Vrai si le nombre est +/- infini, sinon faux
     */
    static bool isInfinity(double value);

    /*!
     *  D�tecte une diff�rence de signe entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param delta Delta
     *
     *  \return Vrai s'il y a une diff�rence de signe, sinon faux
     */
    static bool differentSign(IExpression* function, double x1, double x2, double delta = DELTA);

    /*!
     *  Inverse les deux nombres.
     *
     *  \param x1 Nombre 1
     *  \param x2 Nombre 2
     */
    static void reverse(double& x1, double& x2);

    /*!
     *  Permet de calculer num�riquement une int�grale entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param steps D�coupages
     *
     *  \return Int�grale
     */
    static double integral(IExpression* function, double x1, double x2, int steps = 1000);

    /*!
     *  Permet de calculer num�riquement une tangente.
     *
     *  \param function Fonction
     *  \param x X
     *  \param delta Delta
     *
     *  \return Tangente
     */
    static double tangent(IExpression* function, double x1, double delta = DELTA);

    /*!
     *  Permet de calculer num�riquement un z�ro entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param found Bool�en indiquant si le z�ro a �t� trouv�
     *  \param delta Delta
     *
     *  \return Z�ro
     */
    static double zero(IExpression* function, double x1, double x2, bool* found = NULL, double delta = DELTA);

    /*!
     *  Permet de calculer num�riquement un maximum entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param delta Delta
     *
     *  \return Maximum en x
     */
    static double maximum(IExpression* function, double x1, double x2, double delta = DELTA);

    /*!
     *  Permet de calculer num�riquement un minimum entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param delta Delta
     *
     *  \return Minimum en x
     */
    static double minimum(IExpression* function, double x1, double x2, double delta = DELTA);

    /*!
     *  D�finit le nombre de d�cimales sur un nombre � virgule.
     *
     *  \param value Valeur � arrondir
     *  \param decimal Nombre de d�cimales
     *
     *  \return Valeur arrondie
     */
    static double setDecimal(double value, int decimal);
};

#endif // MATH_TOOLS_H
