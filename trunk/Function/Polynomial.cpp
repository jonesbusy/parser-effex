#include "Polynomial.h"

Polynomial::Polynomial(char variable) :
        AbstractFunction(variable), CONSTANT(1),EXPONENT(1)
{

}

Polynomial::~Polynomial()
{

}


Polynomial::Polynomial(double constant, int exponent, char variable) :
        AbstractFunction(variable), CONSTANT(constant), EXPONENT(exponent)
{

}

Polynomial::Polynomial(int constant, int exponent, char variable) :
        AbstractFunction(variable), CONSTANT(constant), EXPONENT(exponent)
{

}

std::ostream& operator <<(std::ostream& out, const Polynomial& polynomial)
{
    // Valeur indeterminee
    if (polynomial.EXPONENT == 0 || polynomial.CONSTANT == 0)
        return out << polynomial.CONSTANT;

    // On affiche le coefficiant si besoin, puis la variable
    if (polynomial.CONSTANT != 1)
        out << polynomial.CONSTANT;

    out << polynomial.VAR;

    // Afficher l'exposant
    if (polynomial.EXPONENT != 1)
        out << "^" << polynomial.EXPONENT;

    return out;
}


bool operator == (const Polynomial& polynomial1, const Polynomial& polynomial2)
{
    return polynomial1.CONSTANT == polynomial2.CONSTANT && polynomial1.EXPONENT == polynomial2.EXPONENT;
}

bool operator < (const Polynomial& polynomial1, const Polynomial& polynomial2)
{
    return polynomial1.EXPONENT < polynomial2.EXPONENT;
}

Polynomial operator * (const Polynomial& polynomial1, const Polynomial& polynomial2)
{
    return Polynomial(polynomial1.CONSTANT * polynomial2.CONSTANT, polynomial1.EXPONENT + polynomial2.EXPONENT);
}

double Polynomial::eval(double value) const
{
	return this->CONSTANT * pow(value, this->EXPONENT);
}
