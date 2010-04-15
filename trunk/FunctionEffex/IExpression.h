/*******************************************************************
|
| File         : IExpression.h
|
| Description  : Permet de representer de fournir une interface pour
|                evaluer differentes expressions mathematiques ou
|                simples expressions.
|
| Author       : Valentin Delaye
|
| Created      : 07.03.2010
|
| Modified     : -
|
| C++ std      : -
|
| Dependencies :
|
| Version      : 1.0
|
*******************************************************************/

#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#define BUILD_DLL_E

/*
* Inclure ce fichier pour l'export DLL
*/
#ifdef BUILD_DLL_E
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

class DLL_EXPORT IExpression
{

public :

    /***************************************************************
    | Description  : Fonction virtuelle pure. Permet d'evaluer l'
    |                expression a une certaine valeur
    |
    | Visibility   : Public
    |
    | Parameters   : value - Valeur de l'indeterminee
    |
    | Return value : -
    ***************************************************************/
	virtual double eval(double value) const = 0;

};


#endif // EXPRESSION_H_INCLUDED
