#ifndef PARSERMESSAGE_H_INCLUDED
#define PARSERMESSAGE_H_INCLUDED

/**
 *  \file ParserMessage.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 04.04.2010
 *
 *  Les differents messages d'erreur du parseur. Il est possible de changer
 *  la langue moyennant une recompilation. La langue peut-etre changee en
 *  modifiant la constante language.
 */

#include <string>

/*! Language en cours */
const int language = 1;

/*! Caractere inconnu */
const char* const UNKNOWN_CHAR[]           = {"Illegal character found", "Caractere inconnu trouve"};

/*! Nombre attendu */
const char* const DIGIT_EXPECTED[]         = {"Digit expected", "Nombre attendu"};
/*! Operande attendu */
const char* const MISSING_OPERAND[]        = {"Missing operand", "Operande attendu"};
/*! Operateur attendu */
const std::string OPERATOR_EXPECTED[]      = {"Operator expected", "Operateur attendu"};
/*! Parenthese droite attendu */
const std::string RIGHT_PAREN_EXPECTED[]   = {"Right parenthesis expected", "Parenthese droite attendue"};
/*! Parenthese gauche attendue */
const std::string LEFT_PAREN_EXPECTED[]    = {"Left parenthesis expected", "Parenthese gauche attendue"};
/*! Trop de parenthese(s) droite */
const std::string TOO_MANY_RIGHT_PARENT[]  = {"Too many right parenthesis", "Trop de parenthese(s) droite"};
/*! Nom de fonction inconnu */
const std::string UNKNOWN_FUNCTION[]       = {"Unknow name function", "Nom de fonction inconnu"};

#endif // PARSERMESSAGE_H_INCLUDED
