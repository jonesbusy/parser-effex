/*******************************************************************
|
| File         : Operation.h
|
| Description  :
|
| Author       : Valentin Delaye
|
| Created      : 17.03.2010
|
| Modified     : -
|
| C++ std      : -
|
| Dependencies : Expression.h
|
| Version      : 1.0
|
*******************************************************************/

#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include <cmath>

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

public :

    /***************************************************************
    | Description  : Permet de creer une nouvelle operation
    |
    | Visibility   : Public
    |
    | Parameters   : operation - L'operation (+, -, *, /)
    |                left      - Operande de gauche
    |                right     - Operande de droite
    |
    | Return value : -
    ***************************************************************/
    Operation(char operation, IExpression* left, IExpression* right);

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
    | Parameters   : value - Valeur de l'indeterminee
    |
    | Return value : -
    ***************************************************************/
	double eval(double value) const;

};

#endif // OPERATION_H_INCLUDED
