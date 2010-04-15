/*******************************************************************
|
| File         : Parser.h
|
| Description  : Parseur de fonction. Derive Scanner pour analyser
|                la syntaxe des differents token. S'occupe de creer
|                un arbre syntaxique Expression
|
| Author       : Valentin Delaye
|
| Created      : 04.04.2010
|
| Modified     : 17.03.2010 - La parseur construit un arbre
|                             au lieu d'interpreter en temps reel
|                             l'expression
|                30.03.2010 - Export pour compilation d'une DLL
|
| C++ std      : -
|
| Dependencies : Scanner.h
|                I_FactoryFunction.h
|                FactoryPolynomial.h
|                Polynomial.h
|                AbstractFunction.h
|                NamedFunction.h
|                Expression.h
|                Operation.h
|                ParserMessage.h
|
| Version      : 1.0
|
*******************************************************************/

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#define BUILD_DLL_E

/*
* Inclure ce fichier pour l'export DLL
*/
#ifdef BUILD_DLL_E
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif
#include "Scanner.h"

// Fabrication des fonctions
#include "IFactoryFunction.h"
#include "FactoryNamedFunction.h"
#include "FactoryPolynomial.h"

#undef BUILD_DLL_E

// Creation de l'abre syntaxique
#include "Polynomial.h"
#include "AbstractFunction.h"
#include "NamedFunction.h"
#include "IExpression.h"
#include "ParserMessage.h"

#include "Operation.h"

class DLL_EXPORT Parser
{

private :

    /***************************************************************
    | Description  : Analyseur syntaxique
    ***************************************************************/
    Scanner* scanner;

    /***************************************************************
    | Description  : Permet de fabriquer les fonctions polynomiale
    ***************************************************************/
    IFactoryFunction* factoryPolynomial;

    /***************************************************************
    | Description  : Permet de fabriquer les fonctions polynomiale
    ***************************************************************/
    IFactoryFunction* factoryNamedFunction;

    /***************************************************************
    | Description  : Erreur courante du parser
    ***************************************************************/
    ParserError* error;

public :

    /***************************************************************
    | Description  : Permet de creer un nouveau parser
    |
    | Visibility   : Public
    |
    | Parameters   : [input = ""] - La nouvelle chaine d'entree
    |
    | Return value :
    ***************************************************************/
    Parser(std::string input = "");

    /***************************************************************
    | Description  : Supprime le parseur
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value :
    ***************************************************************/
    ~Parser();

    /***************************************************************
    | Description  : Permet de changer la chaine d'entree
    |
    | Visibility   : Public
    |
    | Parameters   : input - La nouvelle chaine d'entree
    |
    | Return value : -
    ***************************************************************/
    void setInput(std::string input);

    /***************************************************************
    | Description  : Permet de parser la chaine
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    IExpression* parse();

    /***************************************************************
    | Description  : Permet de retourner l'erreur du parser
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : L'erreur du parser
    ***************************************************************/
    ParserError* getError() const;

private :


    /***************************************************************
    | Description  : Indique si un token est un operateur ou non
    |
    | Visibility   : Private
    |
    | Parameters   : token - Le token a tester
    |
    | Return value : True c'est un operateur, false sinon
    ***************************************************************/
    bool isOperator(Tokens token) const;

    /***************************************************************
    | Description  : Evaluer une expression
    |
    | Visibility   : Private
    |
    | Parameters   : -
    |
    | Return value : Arbre syntaxique de l'expression
    ***************************************************************/
    IExpression* expression() const;

    /***************************************************************
    | Description  : Evaluer un terme
    |
    | Visibility   : Private
    |
    | Parameters   : -
    |
    | Return value : Arbre syntaxique de l'expression
    ***************************************************************/
    IExpression* term() const;

    /***************************************************************
    | Description  : Evaluer un terme signe
    |
    | Visibility   : Private
    |
    | Parameters   : -
    |
    | Return value : Arbre syntaxique de l'expression
    ***************************************************************/
    IExpression* unary() const;

    /***************************************************************
    | Description  : Evaluer un facteur
    |
    | Visibility   : Private
    |
    | Parameters   : -
    |
    | Return value : Arbre syntaxique de l'expression
    ***************************************************************/
    IExpression* factor() const;

    /***************************************************************
    | Description  : Evaluer un exposant
    |
    | Visibility   : Private
    |
    | Parameters   : -
    |
    | Return value : Arbre syntaxique de l'expression
    ***************************************************************/
    IExpression* exponent() const;

};


#endif // PARSER_H_INCLUDED
