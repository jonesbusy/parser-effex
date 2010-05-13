/*******************************************************************
|
| File         : Polynomial.h
|
| Description  : Permet de representer une fonction polynomiale.
|
| Author       : Valentin Delaye
|
| Created      : 17.02.2010
|
| Modified     : -
|
| C++ std      : ostream, cmath
|
| Dependencies : vector
|
| Version      : 1.0
|
*******************************************************************/

#ifndef MONOMIAL_H_INCLUDED
#define MONOMIAL_H_INCLUDED

#include <ostream>
#include <cmath>

#include "AbstractFunction.h"

class DLL_EXPORT Polynomial : public AbstractFunction
{

public:

    /***************************************************************
    | Description  : Coefficiant du monome
    ***************************************************************/
	const double CONSTANT;

    /***************************************************************
    | Description  : Exposant de la valeur indeterminee
    ***************************************************************/
	const int EXPONENT;

    /***************************************************************
    | Description  : Constructeur. Construit le monome dont le
    |                coefficiant et l'exposant vaut 1. Le monome
    |                vaut donc la valeur de la variable
    |
    | Visibility   : Public
    |
    | Parameters   : variable - La nom de la variable
    |
    | Return value : -
    ***************************************************************/
	explicit Polynomial(char variable = VARIABLE);

    /***************************************************************
    | Description  : Constructeur. Construit le monome dont le
    |                coefficiant et l'exposant est donne
    |
    | Visibility   : Public
    |
    | Parameters   : constant           - Le coefficiant du monome
    |                exponent           - L'exposant du monome
    |                [variable = x]     - La nom de la variable
    |
    | Return value : -
    ***************************************************************/
    Polynomial(double constant, int exponent = 0, char variable = VARIABLE);

    /***************************************************************
    | Description  : Constructeur. Construit le monome dont le
    |                coefficiant et l'exposant est donne
    |
    | Visibility   : Public
    |
    | Parameters   : constant           - Le coefficiant du monome
    |                exponent           - L'exposant du monome
    |                [variable = x]     - La nom de la variable
    |
    | Return value : -
    ***************************************************************/
    Polynomial(int constant, int exponent = 0, char variable = VARIABLE);

    /***************************************************************
    | Description  : Destructeur
    |
    | Visibility   : Public
    |
    | Parameters   :
    |
    | Return value : -
    ***************************************************************/
	virtual ~Polynomial();

    /***************************************************************
    | Description  : Evalue la valeur du monome pour la valeur
    |                donnee
    |
    | Visibility   : Public
    |
    | Parameters   : value            - Valeur de l'indeterminee
    |                [cases = NULL]   - Case pour la detection
    |                                   des discontinuites.
    |                                   (voir Cases.h)
    |
    | Return value : La valeur du monome
    ***************************************************************/
    double eval(double value, Cases* cases = NULL) const;

    /***************************************************************
    | Description  : Permet d'afficher un monome sur le flux
    |
    | Visibility   : Public
    |
    | Parameters   : out      - Le flux
    |                monomial - Le monome a afficher
    |
    | Return value : Le nouveau flux
    ***************************************************************/
	friend std::ostream& operator <<(std::ostream& out, const Polynomial& polynomial);

    /***************************************************************
    | Description  : Permet de comparer deux monome. Les monomes
    |                sont identiques si le coefficiant ainsi que
    |                l'exposant sont les meme
    |
    | Visibility   : Public
    |
    | Parameters   : polynomial1 - Le premier polynomial
    |                polynomial2 - Le deuxieme polynomial
    | Return value : -
    ***************************************************************/
	friend bool operator == (const Polynomial& polynomial1, const Polynomial& polynomial2);

    /***************************************************************
    | Description  : Permet de comparer deux monomes au sens
    |                mathematique, c-a-d si l'exposant est plus
    |                petit ou plus grand
    |
    | Visibility   : Public
    |
    | Parameters   : polynomial1 - Le premier monome
    |                monomial2 - Le deuxieme monome
    | Return value : -
    ***************************************************************/
	friend bool operator < (const Polynomial& polynomial1, const Polynomial& polynomial2);

    /***************************************************************
    | Description  : Permet de multiplier deux monomes
    |
    | Visibility   : Public
    |
    | Parameters   : polynomial1 - Le premier monome
    |                monomial2 - Le deuxieme monome
    | Return value : -
    ***************************************************************/
	friend Polynomial operator * (const Polynomial& polynomial1, const Polynomial& polynomial2);

};

#endif // MONOMIAL_H_INCLUDED
