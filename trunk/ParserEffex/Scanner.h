/*******************************************************************
|
| File         : Scanner.h
|
| Description  : Analyseur lexical d'expression.
|                Permet de transformer la chaine en lexemes qui
|                peuvent etre facilement analysable par un parseur
|
| Author       : Valentin Delaye
|
| Created      : 04.03.2010
|
| Modified     : -
|
| C++ std      :
|
| Dependencies : string, vector
|
| Version      : 1.0
|
*******************************************************************/


#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

#include "AbstractFunction.h"

// Erreurs
#include "ParserError.h"
#include "ParserMessage.h"

/***************************************************************
| Description  : La liste des tokens
***************************************************************/
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

// Le scanner va parser le type de variable configure dans
// AbstractFunction. Doit etre identique pour que le scanner
// fonctionne
const char INDETERMINATE = VARIABLE;

class DLL_EXPORT Scanner
{

private:

    /***************************************************************
    | Description  : La chaine d'entree
    ***************************************************************/
    std::string input;

    /***************************************************************
    | Description  : Buffer pour recuperer les caracteres
    ***************************************************************/
    std::string buffer;

    /***************************************************************
    | Description  : Identifiant sour forme de chaine
    |                (ex, sin, cos)
    ***************************************************************/
    std::string identifier;

    /***************************************************************
    | Description  : Les nom sous forme de chaine des token
    ***************************************************************/
    std::vector<std::string> tokenNames;

    /***************************************************************
    | Description  : Le charactere courant, non traite
    ***************************************************************/
    char currentChar;

    /***************************************************************
    | Description  : Permet de compter le nombre de paranthese
    |                gauche
    ***************************************************************/
    int nbLeftParen;

    /***************************************************************
    | Description  : Permet de compter le nombre de paranthese
    |                droite
    ***************************************************************/
    int nbRightParen;

public :

    /***************************************************************
    | Description  : Permet de creer un nouveau scanner
    |
    | Visibility   : Public
    |
    | Parameters   : input - La chaine d'entree
    |
    | Return value :
    ***************************************************************/
    Scanner(std::string input);

    /***************************************************************
    | Description  : Permet de changer la nouvelle chaine d'entree
    |
    | Visibility   : Public
    |
    | Parameters   : input - La nouvelle chaine d'entree
    |
    | Return value :
    ***************************************************************/
    void setInput(std::string input);

    /***************************************************************
    | Description  : Permet de se deplacer au prochain token
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    void nextToken();

    /***************************************************************
    | Description  : Permet de retourne la classe du token
    |                sous-forme de chaine du token
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value : Le nom du token
    ***************************************************************/
    std::string currentTokenName() const;

    /***************************************************************
    | Description  : Permet de retourne la representation complete
    |                du token
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value : La representation du token
    ***************************************************************/
    std::string representation() const;


    /***************************************************************
    | Description  : Permet d'indiquer si le scanner a termine
    |                l'analyse des token
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value : True le scanner a termine, false sinon
    ***************************************************************/
    bool hasFinished() const;

    /***************************************************************
    | Description  : Permet de au prochain caractere interessant en
    |                sautant les espaces
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    void nextChar();

    /***************************************************************
    | Description  : Permet d'aller au prochaine caractere de la
    |                chaine
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    void next();

    /***************************************************************
    | Description  : Permet de reinitialiser les valeurs et de
    |                remettre 0 le scanner
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    void clean();

    /***************************************************************
    | Description  : Permet de recuperer l'identifiant sous forme
    |                de chaine
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    std::string getIdentifier();

    /***************************************************************
    | Description  : Permet d'indiquer si la caractere courant est
    |                est une variable
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : True la caractere est une variable, false
    |                sinon
    ***************************************************************/
    bool isVariable(char);

    /***************************************************************
    | Description  : Permet d'indiquer si le scanner a detecte le
    |                meme nombre de parantheses.
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : 0 meme nombre, -1 moin de gauche, 1 moin de
    |                droite
    ***************************************************************/
    int egalityParen();


    /***************************************************************
    | Description  : Le token courant
    ***************************************************************/
    Tokens currentToken;

    /***************************************************************
    | Description  : Position du token courant
    ***************************************************************/
    int currentTokenPosition;


};

#endif // SCANNER_H_INCLUDED
