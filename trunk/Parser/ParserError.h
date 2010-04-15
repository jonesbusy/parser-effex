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
| Modified     : 14.03.2010 - Ajout de getMessage et getPosition
|
| C++ std      : string
|                sstream
|                exception
|
| Dependencies : -
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
    | Description  : Permet de retourner le message d'erreur entier
    |                (message + at postion + position)
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : Le message d'erreur
    ***************************************************************/
    virtual const char* what() const throw();

    /***************************************************************
    | Description  : Permet de retourner uniquement le message
    |                d'erreur
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : Le message d'erreur
    ***************************************************************/
    std::string getMessage() const;

    /***************************************************************
    | Description  : Permet de retourner la position de l'erreur
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : La position de l'erreur
    ***************************************************************/
    int getPosition() const;

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
