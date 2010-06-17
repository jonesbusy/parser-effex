/*!
 *  \mainpage Parseur
 *  \section Description
 *  Le parseur s'occupe de convertir une chaine de caractere en un
 *  objet IExpression. Il utilise pour cela un analyseur lexical pour
 *  faciliter le parsage.
 */

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

/*!
 *  \file Parser.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 04.04.2010
 *
 *  Parseur de fonction. Permet de parser une chaine d'entree
 *  d'entree et de creer une structure IExpression.
 */

#include "ParserExport.h"

// Fabrication des fonctions
#include "Scanner.h"
#include "IFactoryFunction.h"
#include "FactoryNamedFunction.h"
#include "FactoryPolynomial.h"

// Creation de l'abre syntaxique
#include "Polynomial.h"
#include "AbstractFunction.h"
#include "NamedFunction.h"
#include "IExpression.h"
#include "ParserMessage.h"
#include "Operation.h"

#undef DLL_EXPORT

#ifdef BUILD_DLL_PARSER
    /*! Pour l'export DLL */
    #define DLL_EXPORT __declspec(dllexport)
#else
    /*! Pour l'import DLL */
    #define DLL_EXPORT __declspec(dllimport)
#endif

/*! \class Parser
 *
 * Permet de representer un parser. Utilise les service de l'analyseur
 * syntaxique pour recuperer le prochain token et analyser la suite
 * de tokens. Permet de construire un arbre binaire IExpression.
 */
class DLL_EXPORT Parser
{
    private :

    /*! Analyseur syntaxique */
    Scanner* scanner;

    /*! Permet de fabriquer les fonctions polynomiale */
    IFactoryFunction* factoryPolynomial;

    /*! Permet de fabriquer les fonctions nommees */
    IFactoryFunction* factoryNamedFunction;

    /*! Erreur courante du parser */
    ParserError* error;



    public :

    /*!
     *  Constructeur. Permet de creer un nouveau parser.
     *
     *  \param input La chaine d'entree
     *
     */
    Parser(std::string input = "");

    /*!
     *  Desctructeur.
     */
    ~Parser();

    /*!
     *  Permet de changer la chaine d'entree. Le parseur est
     *  reinitialise pour le parsage de la nouvelle chaine.
     *
     *  \param input La chaine d'entree
     */
    void setInput(std::string input);

    /*!
     *  Permet de parser la chaine et de retourner une expression.
     *
     *  \return L'expression ou null si erreur
     */
    IExpression* parse();

    /*!
     *  Permet de retourner l'erreur du parseur.
     *
     *  \return L'erreur du parseur
     */
    ParserError* getError() const;



    private :

    /*!
     *  Indique si un token est un operateur ou non.
     *
     *  \param token Le token a analyser
     *  \return True c'est un operateur, false sinon
     */
    bool isOperator(Tokens token) const;

    /*!
     *  Permet de retourner le sous arbre d'une expression.
     *  \return Le sous arbre IExpression
     */
    IExpression* expression() const;

    /*!
     *  Permet de retourner le sous arbre d'un terme.
     *  \return Le sous arbre IExpression
     */
    IExpression* term() const;

    /*!
     *  Permet de retourner le sous arbre d'un membre unaire.
     *  \return Le sous arbre IExpression
     */
    IExpression* unary() const;

    /*!
     *  Permet de retourner le sous arbre d'un facteur.
     *  \return Le sous arbre IExpression
     */
    IExpression* factor() const;

    /*!
     *  Permet de retourner le sous arbre d'un exposant.
     *  \return Le sous arbre IExpression
     */
    IExpression* exponent() const;

};


#endif // PARSER_H_INCLUDED
