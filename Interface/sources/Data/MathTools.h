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
 *  \brief La classe statique MathTools proposes des outils mathématiques.
 *
 *  Cette classe permet de calculer numériquement des intégrales, des
 *  tangentes, des zéros, des maximums ou des minimums. Elle propose aussi des
 *  méthodes statiques pour détecter un NaN ou une infinitée...
 */

class MathTools
{
    private:

    /*! Delta par défaut */
    static const double DELTA = 0.0001;



    public:

    /*!
     *  Détermine si un nombre est de type "NaN".
     *
     *  \param value Nombre à tester
     *
     *  \return Vrai si le nombre est de type "NaN", sinon faux
     */
    static bool isNaN(double value);

    /*!
     *  Détermine si un nombre est +/- infini.
     *
     *  \param value Nombre à tester
     *
     *  \return Vrai si le nombre est +/- infini, sinon faux
     */
    static bool isInfinity(double value);

    /*!
     *  Détecte une différence de signe entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param delta Delta
     *
     *  \return Vrai s'il y a une différence de signe, sinon faux
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
     *  Permet de calculer numériquement une intégrale entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param steps Découpages
     *
     *  \return Intégrale
     */
    static double integral(IExpression* function, double x1, double x2, int steps = 1000);

    /*!
     *  Permet de calculer numériquement une tangente.
     *
     *  \param function Fonction
     *  \param x X
     *  \param delta Delta
     *
     *  \return Tangente
     */
    static double tangent(IExpression* function, double x1, double delta = DELTA);

    /*!
     *  Permet de calculer numériquement un zéro entre deux bornes.
     *
     *  \param function Fonction
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *  \param found Booléen indiquant si le zéro a été trouvé
     *  \param delta Delta
     *
     *  \return Zéro
     */
    static double zero(IExpression* function, double x1, double x2, bool* found = NULL, double delta = DELTA);

    /*!
     *  Permet de calculer numériquement un maximum entre deux bornes.
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
     *  Permet de calculer numériquement un minimum entre deux bornes.
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
     *  Définit le nombre de décimales sur un nombre à virgule.
     *
     *  \param value Valeur à arrondir
     *  \param decimal Nombre de décimales
     *
     *  \return Valeur arrondie
     */
    static double setDecimal(double value, int decimal);
};

#endif // MATH_TOOLS_H
