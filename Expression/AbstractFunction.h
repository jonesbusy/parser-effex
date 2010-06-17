#ifndef ABSTRACT_FUNCTION_H_INCLUDED
#define ABSTRACT_FUNCTION_H_INCLUDED

/**
 * \file AbstractFunction.h
 * \author Valentin Delaye
 * \version 1.0
 * \date 04.03.2010
 *
 * Permet de representer une classe de base pour les fonctions.
 */

#include <iostream>

#include "ExpressionExport.h"
#include "IExpression.h"

/*! Caractere de la variable */
const char VARIABLE = 'x';

/*! \class AbstractFunction
 *
 * Classe abstraite qui sert de base pour les fonctions.
 */
class DLL_EXPORT AbstractFunction : public IExpression
{
    public :

    /*! Nom de la variable de ce type de fonction */
    const char VAR;

    /*! Valeur courante de l'indeterminee (generalement x) */
	static double defaultValue;



    public :

    /*!
     *  Constructeur, permet de constuire une fonction.
     *
     *  \param variable Caractere de la variable de la fonction
     */
    explicit AbstractFunction(char variable = VARIABLE);

    /*!
     *  Destructeur.
     */
	virtual ~AbstractFunction();

    /*!
     *  Evaluer la fonction. Fonction virtuelle pure. Permet d'evaluer
     *  la fonction a une certaine valeur.
     *  Doit etre redefinie pour toutes les fonctions.
     *
     *  \param value Valeur de l'indeterminee
     *  \param cases Case pour la detection des discontinuites.
     *   (voir Cases.h)
     *  \return La valeur d'evaluation (y = ...)
     */
	virtual double eval(double value, Cases* cases = NULL) const = 0;

    /*!
     *  Operateur (). Permet d'evaluer la fonction. Utilise la valeur defaultValue
     *  pour effectuer l'evaluation. Cette variable peut-etre changee
     *  grace a la methode setEval(double).
     */
	operator double() const;

    /*!
     *  Permet de changer la valeur par defaut d'evaluation.
     *
     * \param value La nouvelle valeur
     */
	static void setEval(double value);
};

#endif // ABSTRACT_FUNCTION_H_INCLUDED
