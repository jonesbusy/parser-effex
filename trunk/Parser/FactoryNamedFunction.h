/*******************************************************************
|
| File         : FactoryNamedFunction.h
|
| Description  : Classe permettant de creer les differents type de
|                fonction nomme suivant leur nom
|
| Author       : Valentin Delaye
|
| Created      : 03.03.2010
|
| Modified     : -
|
| C++ std      : map
|                string
|                exception
|                cmath
|
| Dependencies : NamedFunction.h
|                FactoryFunction.h
|
| Version      : 1.0
|
*******************************************************************/

#ifndef FACTORYNAMEDFUNCTION_H_INCLUDED
#define FACTORYNAMEDFUNCTION_H_INCLUDED

#include <map>
#include <string>
#include <exception>
#include <cmath>

#include "NamedFunction.h"
#include "IFactoryFunction.h"

class FactoryNamedFunction : public IFactoryFunction
{

public :

    /***************************************************************
    | Description  : Permet de creer la nouvelle fabrique de
    |                de fonction nommee
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    FactoryNamedFunction();

    /***************************************************************
    | Description  : Permet de supprimer la fabrique de fonction
    |                nommee
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    virtual ~FactoryNamedFunction();

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
    NamedFunction* getInstance(std::string name) const;

private :

    /***************************************************************
    | Description  : Permettant de faire correspondre le nom de la
    |                fonction a la fonction elle meme
    ***************************************************************/
    std::map<std::string, double(*)(double)> functions;

};

#endif // FACTORYNAMEDFUNCTION_H_INCLUDED
