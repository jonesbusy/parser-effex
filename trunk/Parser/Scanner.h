#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

/**
 *  \file Scanner.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 04.03.2010
 *
 *  Analyseur lexical d'expression.
 *  Permet de transformer la chaine en lexemes qui
 *  peuvent etre facilement analysable par un parseur.
 *
 */

#include <string>
#include <vector>
#include <iostream>

#include "AbstractFunction.h"

// Erreurs
#include "ParserError.h"
#include "ParserMessage.h"

/*! La liste des tokens */
enum Tokens
{
    END_OF_LINE,
    NAMED_FONCTION,
    POLYNOMIAL,
	LEFT_PAREN,
	RIGHT_PAREN,
	PLUS,
	MINUS,
	TIMES,
	DIV,
	POW,
	UNKNOWN
};


/*!
 *  Le scanner va parser le type de variable configure dans
 *  AbstractFunction. Doit etre identique pour que le scanner
 *  fonctionne.
 */
const char INDETERMINATE = VARIABLE;

/*! \class Scanner
 *
 *  Analyseur syntaxique
 */
class Scanner
{
    public :

    /*! Le token courant */
    Tokens currentToken;

     /*! Position du token courant */
    int currentTokenPosition;



    private:

    /*! La chaine d'entree */
    std::string input;

    /*! Buffer pour recuperer les caractres*/
    std::string buffer;

    /*! Identifiant sour forme de chaine (ex, sin, cos) */
    std::string identifier;

    /*! Les nom sous forme de chaine des token */
    std::vector<std::string> tokenNames;

    /*! Le charactere courant, non traite */
    char currentChar;

    /*! Permet de compter le nombre de paranthese gauche */
    int nbLeftParen;

    /*! Permet de compter le nombre de paranthese droite */
    int nbRightParen;



    public :

    /*!
     *  Constructeur. Permet de creer un nouveau scanner d'expression.
     *
     *  \param input La chaine d'entree.
     */
    Scanner(std::string input);

    /*!
     *  Permet de changer la nouvelle chaine d'entree.
     *
     *  \param input La nouvelle chaine d'entree
     */
    void setInput(std::string input);

    /*!
     * Permet de se deplacer au prochain token.
     */
    void nextToken();

    /*!
     *  Permet de retourner la token sous forme de chaine.
     *
     *  \return Le nom du token
     */
    std::string currentTokenName() const;

    /*!
     *  Permet de retourner la representation complete du token.
     *
     *  \return La representation complete.
     */
    std::string representation() const;

    /*!
     *  Permet d'indiquer si le scanner a termine de scanner la chaine.
     *
     *  \return True le scanner a termine, false sinon
     */
    bool hasFinished() const;

    /*!
     *  Permet de se deplacer au prochain caractere different d'un espace.
     */
    void nextChar();

    /*!
     * Permet de se deplacer au prochain caractere de la chaine.
     */
    void next();

    /*!
     * Permet de remettre a 0 le scanner.
     */
    void clean();

    /*!
     *  Permet de recuperer l'identifiant sous forme de chaine.
     *  \return L'identifiant
     */
    std::string getIdentifier();

    /*!
     *  Permet d'indiquer si le caractere courant est une variable ou non.
     *
     *  \return True c'est une variable, false sinon
     */
    bool isVariable(char);

    /*!
     *  Permet d'indiquer si le scanner a detecter le meme nombre
     *  de parentheses.
     *
     *  \return 0 : meme nombre, -1 : moin de gauche, 1 : moin de droite
     */
    int egalityParen();


};

#endif // SCANNER_H_INCLUDED
