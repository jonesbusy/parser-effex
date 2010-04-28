/*******************************************************************
|
| File         : ParserMessage.h
|
| Description  : Fourni differents message d'erreur pour les modules
|                suivants : Scanner, Parser, Factory
|
| Author       : Valentin Delaye
|
| Created      : 04.03.2010
|
| Modified     : 28.04.2010 - Ajout de la langue francaise
|
| C++ std      : string
|
| Dependencies :
|
| Version      : 1.0
|
*******************************************************************/

#ifndef PARSERMESSAGE_H_INCLUDED
#define PARSERMESSAGE_H_INCLUDED

#include <string>

const int language = 1;

// Scanner
const char* const UNKNOWN_CHAR[]           = {"Illegal character found", "Caractere inconnu trouve"};

// Parser
const char* const DIGIT_EXPECTED[]         = {"Digit expected", "Nombre attendu"};
const char* const MISSING_OPERAND[]        = {"Missing operand", "Operande attendu"};
const std::string OPERATOR_EXPECTED[]      = {"Operator expected", "Operateur attendu"};
const std::string RIGHT_PAREN_EXPECTED[]   = {"Right parenthesis expected", "Parenthese droite attendue"};
const std::string LEFT_PAREN_EXPECTED[]    = {"Left parenthesis expected", "Parenthese gauche attendue"};
const std::string TOO_MANY_RIGHT_PARENT[]  = {"Too many right parenthesis", "Trop de parenthese(s) droite"};
const std::string UNKNOWN_FUNCTION[]       = {"Unknow name function", "Nom de fonction inconnu"};

#endif // PARSERMESSAGE_H_INCLUDED
