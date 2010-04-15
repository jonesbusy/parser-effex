/*******************************************************************
|
| File         : AbstractFunction.h
|
| Description  : Classe abstraite qui sert de base pour les
|                fonctions
|
| Author       : Valentin Delaye
|
| Created      : 04.03.2010
|
| Modified     : -
|
| C++ std      :
|
| Dependencies :
|
| Version      : 1.0
|
*******************************************************************/


#ifndef ABSTRACT_FUNCTION_H_INCLUDED
#define ABSTRACT_FUNCTION_H_INCLUDED

#include <iostream>

#include "IExpression.h"

const char VARIABLE = 'x';

class DLL_EXPORT AbstractFunction : public IExpression
{


public :

    /***************************************************************
    | Description  : Constructeur, permet de constuire une fonction
    |
    | Visibility   : Public
    |
    | Parameters   : [variable = VARIABLE] - Variable de la fonction
    |
    | Return value : -
    ***************************************************************/
    AbstractFunction(char variable = VARIABLE);

    /***************************************************************
    | Description  : Destructeur, permet de detruire une fonction
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value : -
    ***************************************************************/
	virtual ~AbstractFunction();

    /***************************************************************
    | Description  : Fonction virtuelle pure. Permet d'evaluer la
    |                fonction a une certaine valeur
    |
    | Visibility   : Public
    |
    | Parameters   : value - Valeur de l'indeterminee
    |
    | Return value : -
    ***************************************************************/
	virtual double eval(double value) const = 0;

    /***************************************************************
    | Description  : Permet d'evaluer la fonction avec la valeur
    |                par defaut. Utilise le polymorphisme sur les
    |                fonctions avec eval(double)
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value : -
    ***************************************************************/
	operator double() const;

    /***************************************************************
    | Description  : Permet de changer la valeur par defaut
    |                de l'evaluation.
    |
    | Visibility   : Public
    |
    | Parameters   : value - La nouvelle valeur
    |
    | Return value : -
    ***************************************************************/
	static void setEval(double value);

    /***************************************************************
    | Description  : Nom de la variable de ce type de fonction
    ***************************************************************/
    const char VAR;

public :

    /***************************************************************
    | Description  : Valeur courante de l'indeterminee
    |               (generalement x)
    ***************************************************************/
	static double defaultValue;

};

#endif // ABSTRACT_FUNCTION_H_INCLUDED
