/*******************************************************************
|
| File         : FactoryPolynomial.h
|
| Description  : Permet de creer une fonction polynomialr suivant
|                une chaine de caractere.
|
| Author       : Valentin Delaye
|
| Created      : 10.03.2010
|
| Modified     : -
|
| C++ std      : string
|                map
|
| Dependencies : Polynomial.h
|                I_FactoryFunction.h
|
| Version      : 1.0
|
*******************************************************************/

#ifndef FACTORYPOLYNOMIAL_H_INCLUDED
#define FACTORYPOLYNOMIAL_H_INCLUDED


#include "IFactoryFunction.h"
#include "Polynomial.h"

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

class FactoryPolynomial : public IFactoryFunction
{

public :

    /***************************************************************
    | Description  : Permet de creer la nouvelle fabrique de
    |                de fonction polynomiale
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    FactoryPolynomial();

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
    virtual ~FactoryPolynomial();

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
    Polynomial* getInstance(std::string name) const;


private :

    /***************************************************************
    | Description  : Permettant de faire correspondre le nom de la
    |                constantes a la valeur de la constante
    ***************************************************************/
    std::map<std::string, double> constants;


    /***************************************************************
    | Description  : Indique si un caractere donne se trouve a la
    |                possition donnee dans la chaine
    |
    | Visibility   : Public
    |
    | Parameters   : input - La chaine de caractere
    |                position - La position du caractere
    |                value - La valeur du caractere
    |
    | Return value : True si la caractere se trouve bien a l
    |                position donnee. False sinon ou si la position
    |                est en dehors de la chaine
    ***************************************************************/
    bool isCharAt(std::string input, size_t position, char value) const;


    /***************************************************************
    | Description  : Indique si un digit donne se trouve a la
    |                possition donnee dans la chaine
    |
    | Visibility   : Public
    |
    | Parameters   : input - La chaine de caractere
    |                position - La position du caractere
    |
    | Return value : True si la digit se trouve bien a l
    |                position donnee. False sinon ou si la position
    |                est en dehors de la chaine
    ***************************************************************/
    bool isDigitAt(std::string input, size_t position) const;

};

#endif // FACTORYPOLYNOMIAL_H_INCLUDED
