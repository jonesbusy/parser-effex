#ifndef NAMEDFUNCTIONS_H_INCLUDED
#define NAMEDFUNCTIONS_H_INCLUDED

/**
 * \file NamedFunction.h
 * \author Valentin Delaye
 * \version 1.0
 * \date 03.03.2010
 *
 * Permet de representer une function nommee telle que
 * sin, cos, abs, etc.
 */

#include <string>
#include <cmath>
#include <iostream>

#include "ExpressionExport.h"
#include "AbstractFunction.h"

/*! \class NamedFunction
 *
 * Permet de representer une fonction nommee
 */
class DLL_EXPORT NamedFunction : public AbstractFunction
{
    private :

    /*! Nom de la fonction */
    std::string name;

    /*! Fonction mathematique associee */
    double (*function)(double);



    public :

    /*!
     *  Constructeur, creer un fonction nommee
     *
     *  \param name Nom de la fonction
     *  \param function Fonction mathematique associee
     */
    NamedFunction(std::string name, double(*function)(double));

    /*!
     *  Permet d'evaluer la fonction nommee.
     *
     *  \param value Valeur d'evaluation
     *  \param cases Le case pour les discontinuites
     *  \return La valeur d'evaluation (y = ...)
     */
    double eval(double value, Cases* cases = NULL) const;

    /*!
     *  Operateur (). Permet d'evaluer la fonction nommee.
     *
     *  \param value Valeur d'evaluation
     */
    double operator()(double value) const;

};

#endif // NAMEDFUNCTIONS_H_INCLUDED
