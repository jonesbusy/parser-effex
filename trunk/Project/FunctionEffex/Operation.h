/*******************************************************************
|
| File         : Operation.h
|
| Description  : Permet d'effectuer une operation sur un noeud de
|                l'arbre
|
| Author       : Valentin Delaye
|
| Created      : 17.03.2010
|
| Modified     : 12.05.2010 - Add name attribute for function
|
| C++ std      : cmath
|                string
|
| Dependencies : Expression.h
|
| Version      : 2.0
|
*******************************************************************/

#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include <cmath>
#include <string>

#define PI 3.141592653589794

#include "IExpression.h"

class DLL_EXPORT Operation : public IExpression
{

private :

    /***************************************************************
    | Description  : Operation associee
    ***************************************************************/
    char operation;

    /***************************************************************
    | Description  : Expression gauche
    ***************************************************************/
    IExpression* left;

    /***************************************************************
    | Description  : Expression droite
    ***************************************************************/
    IExpression* right;

    /***************************************************************
    | Description  : Nom de la fonction (si fonction unaire)
    ***************************************************************/
    std::string name;

public :

    /***************************************************************
    | Description  : Permet de creer une nouvelle operation
    |
    | Visibility   : Public
    |
    | Parameters   : operation     - L'operation (+, -, *, /, f)
    |                left          - Operande de gauche
    |                right         - Operande de droite
    |                [name = ""] - Nom de la fonction
    |
    | Return value : -
    ***************************************************************/
    Operation(char operation, IExpression* left, IExpression* right, std::string name = "");

    /***************************************************************
    | Description  : Permet de supprimer une operation
    |
    | Visibility   :
    |
    | Parameters   :
    |
    | Return value : -
    ***************************************************************/
	virtual ~Operation();

    /***************************************************************
    | Description  : Permet d'evaluer l' expression a une certaine
    |                valeur
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

};

#endif // OPERATION_H_INCLUDED
