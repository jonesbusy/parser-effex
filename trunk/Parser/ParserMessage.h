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
const std::string EN_UNKNOWN_CHAR          = "Illegal character found";

// Parser
const std::string EN_DIGIT_EXPECTED        = "Digit expected";
const std::string EN_MISSING_OPERAND       = "Missing operand";
const std::string EN_OPERATOR_EXPECTED     = "Operator expected";
const std::string EN_RIGHT_PAREN_EXPECTED  = "Right parenthesis expected";
const std::string EN_LEFT_PAREN_EXPECTED   = "Left parenthesis expected";
const std::string EN_TOO_MANY_RIGHT_PARENT = "Too many right parenthesis";
const std::string EN_UNKNOWN_FUNCTION      = "Unknow name function";

#endif // PARSERMESSAGE_H_INCLUDED
