/*******************************************************************
|
| File         : FactoryFunction.h
|
| Description  : Interface (Abstract Factory) permettant de creer
|                divers type de fonctions
|
| Author       : Valentin Delaye
|
| Created      : 03.03.2010
|
| Modified     : -
|
| C++ std      : string
|
| Dependencies : AbstractFunction.h
|
| Version      : 1.0
|
*******************************************************************/

#ifndef FACTORYFUNCTION_H_INCLUDED
#define FACTORYFUNCTION_H_INCLUDED

#include <string>

#include "AbstractFunction.h"

class IFactoryFunction
{

public:

    /***************************************************************
    | Description  : Permet retourner une instance de fonction
    |                nommee suivant son nom.
    |
    | Visibility   : Public
    |
    | Parameters   : name - La nom de la fonction
    |
    | Return value : L'instance de la fonction nomme
    ***************************************************************/
    virtual AbstractFunction* getInstance(std::string name) const = 0;

};


#endif // FACTORYFUNCTION_H_INCLUDED
