#ifndef MONOMIAL_H_INCLUDED
#define MONOMIAL_H_INCLUDED

/**
 *  \file Polynomial.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 17.02.2010
 *
 *  Permet de fournir une structure pour les fonctions
 *  polynomiales.
 */

#include <ostream>
#include <cmath>

#include "ExpressionExport.h"
#include "AbstractFunction.h"

/*! \class Polynomial
 *
 * Represente un polynome.
 */
class DLL_EXPORT Polynomial : public AbstractFunction
{
    public :

    /*! Le coefficiant */
	const double CONSTANT;

    /*! L'exposant */
	const int EXPONENT;



	public :

    /*!
     *  Constructeur, permet de constuire un polynome. Le polynome
     *  construit vaut x.
     *
     *  \param variable Caractere de la variable de la fonction
     */
	explicit Polynomial(char variable = VARIABLE);

    /*!
     *  Constructeur, permet de constuire un polynome. Le coefficiant
     *  et l'exposant sont donnees en parametre
     *
     *  \param constant Le coefficiant du monome
     *  \param exponent L'exposant
     *  \param variable Caractere de la variable de la fonction
     */
    Polynomial(double constant, int exponent = 0, char variable = VARIABLE);

    /*!
     *  Constructeur, permet de constuire un polynome. Le coefficiant
     *  et l'exposant sont donnees en parametre
     *
     *  \param constant Le coefficiant du monome
     *  \param exponent L'exposant
     *  \param variable Caractere de la variable de la fonction
     */
    Polynomial(int constant, int exponent = 0, char variable = VARIABLE);

    /*!
     * Destructeur
     */
	virtual ~Polynomial();

    /*!
     *  Permet d'evaluer le polynome.
     *
     *  \param value Valeur d'evaluation
     *  \param cases Le case pour les discontinuites
     *  \return La valeur d'evaluation (y = ...)
     */
    double eval(double value, Cases* cases = NULL) const;

    /*!
     *  Permet d'afficher un polynome.
     *
     *  \param out Flux d'entree
     *  \param polynomial Le polynome
     *  \return Le flux modifie
     */
	friend std::ostream& operator <<(std::ostream& out, const Polynomial& polynomial);

    /*!
     *  Permet de comparer deux polynomes. Se base sur le coefficiant
     *  et l'exposant pour comparer les polynomes.
     *
     *  \param polynomial1 Premier polynome
     *  \param polynomial2 Deuxieme polynome
     *  \return True si les polygones sont egaux, false sinon
     */
	friend bool operator == (const Polynomial& polynomial1, const Polynomial& polynomial2);

    /*!
     *  Permet de comparer deux polynomes au sens mathematique du terme.
     *  Se base donc sur l'exposant pour comparer les polynomes.
     *
     *  \param polynomial1 Premier polynome
     *  \param polynomial2 Deuxieme polynome
     *  \return True le premier polygone est strictement plus petit que le deuxieme,
     *   false sinon.
     */
	friend bool operator < (const Polynomial& polynomial1, const Polynomial& polynomial2);


    /*!
     *  Permet de multiplier deux polynomes.
     *
     *  \param polynomial1 Premier polynome
     *  \param polynomial2 Deuxieme polynome
     *  \return Le nouveau polynome
     */
	friend Polynomial operator * (const Polynomial& polynomial1, const Polynomial& polynomial2);

};

#endif // MONOMIAL_H_INCLUDED
