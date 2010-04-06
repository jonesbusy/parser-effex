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
| Modified     : -
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

// Scanner
const std::string UNKNOWN_CHAR          = "Illegal character found";

// Parser
const std::string DIGIT_EXPECTED        = "Digit expected";
const std::string MISSING_OPERAND       = "Missing operand";
const std::string OPERATOR_EXPECTED     = "Operator expected";
const std::string RIGHT_PAREN_EXPECTED  = "Right parenthesis expected";
const std::string LEFT_PAREN_EXPECTED   = "Left parenthesis expected";
const std::string TOO_MANY_RIGHT_PARENT = "Too many right parenthesis";
const std::string UNKNOWN_FUNCTION      = "Unknow name function";

#endif // PARSERMESSAGE_H_INCLUDED
