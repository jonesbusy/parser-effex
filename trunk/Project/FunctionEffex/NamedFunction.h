/*******************************************************************
|
| File         : NamedFunction.h
|
| Description  : Permet de representer
|                une function nommee telle que sin, cos, abs, etc.
|
| Author       : Valentin Delaye
|
| Created      : 03.03.2010
|
| Modified     : -
|
| C++ std      : string, cmath
|
| Dependencies : AbstractFunction.h
|
| Version      : 1.0
|
*******************************************************************/

#ifndef NAMEDFUNCTIONS_H_INCLUDED
#define NAMEDFUNCTIONS_H_INCLUDED

#include <string>
#include <cmath>
#include <iostream>

#include "AbstractFunction.h"

class DLL_EXPORT NamedFunction : public AbstractFunction
{

private :

    /***************************************************************
    | Description  : Nom de la fonction
    ***************************************************************/
    std::string name;

    /***************************************************************
    | Description  : Fonction mathematique associee
    ***************************************************************/
    double (*function)(double);

public :

    /***************************************************************
    | Description  : Constructeur, creer un fonction nommee
    |
    | Visibility   : Public
    |
    | Parameters   : name       - Le nom de la fonction
    |                function   - La fonction mathematique
    |
    | Return value : -
    ***************************************************************/
    NamedFunction(std::string name, double(*function)(double));

    /***************************************************************
    | Description  : Evalue la fonction nommee
    |
    | Visibility   : Public
    |
    | Parameters   : value            - Valeur de l'indeterminee
    |                [cases = NULL]   - Case pour la detection
    |                                   des discontinuites.
    |                                   (voir Cases.h)
    |
    | Return value : -
    ***************************************************************/
    double eval(double value, Cases* cases = NULL) const;

    /***************************************************************
    | Description  : Evalue la fonction nommee a une certaine valeur
    |
    | Visibility   : Public
    |
    | Parameters   : value - La valeur d'evaluation
    |
    | Return value : -
    ***************************************************************/
    double operator()(double value) const;

};

#endif // NAMEDFUNCTIONS_H_INCLUDED
