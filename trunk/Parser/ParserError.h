/*******************************************************************
|
| File         : ParserError.h
|
| Description  : Permettre de representer une erreur de parsage
|                l'erreur est representee par un message et une
|                position d'erreur
|
| Author       : Valentin Delaye
|
| Created      : 04.03.2010
|
| Modified     : -
|
| C++ std      : string
|                sstream
|                exception
|
| Dependencies :
|
| Version      : 1.0
|
*******************************************************************/

#ifndef PARSERERROR_H_INCLUDED
#define PARSERERROR_H_INCLUDED

#include <string>
#include <sstream>
#include <exception>

class ParserError : public std::exception
{

public :

    /***************************************************************
    | Description  : Permet de creer une nouvelle erreur
    |
    | Visibility   : Public
    |
    | Parameters   : message    - Le message d'erreur
    |                position   - La position dans la ligne
    | Return value :
    ***************************************************************/
    ParserError(std::string message, int position) throw();


    /***************************************************************
    | Description  : Supprimer l'exception
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value :
    ***************************************************************/
    virtual ~ParserError() throw();


    /***************************************************************
    | Description  : Permet de retourner le message d'erreur
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value :
    ***************************************************************/
    virtual const char* what() const throw();

private :

    /***************************************************************
    | Description  : Le message d'erreur
    ***************************************************************/
    std::string message;

    /***************************************************************
    | Description  : La position de l'erreur
    ***************************************************************/
    int position;

};

#endif // PARSERERROR_H_INCLUDED
