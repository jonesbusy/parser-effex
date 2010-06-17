#ifndef FACTORYPOLYNOMIAL_H_INCLUDED
#define FACTORYPOLYNOMIAL_H_INCLUDED

/*!
 *  \file FactoryPolynomial.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 10.03.2010
 *
 *  Permettre de fabriquer des polynomes.
 */

#include "IFactoryFunction.h"
#include "Polynomial.h"

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

/*! \class FactoryPolynomial
 *
 *  Fabrique concrete de polynomes. Permet de fabriquer
 *  des objets Polynomial.
 */
class FactoryPolynomial : public IFactoryFunction
{
    private :

    /*!
    *  Permet de faire correspondre le nom de la
    *  constante a sa valeur numerique.
    */
    std::map<std::string, double> constants;



    public :

    /*!
     * Constructeur. Permet de creer la nouvelle fabrique.
     */
    FactoryPolynomial();

    /*!
     * Destructeur.
     */
    virtual ~FactoryPolynomial();

    /*!
     *  Permet de retourner une instance d'un polynome
     *  suivant une chaine de caractere representant le polynome.
     *
     *  \param name Le polynome
     *  \return L'instance du polynome ou null si impossible
     *  de creer le polynome.
     */
    Polynomial* getInstance(std::string name) const;



    private :

    /*!
     *  Indique si un caractere donnee se trouve a la position donee
     *  dans la chaine.
     *
     * \param input La chaine de caractere
     * \param position La position du caractere
     * \param value Le caractere
     * \return True si le caractere se trouve bien a la position
     *  donnee. False sinon, ou si la position est en dehors de la chaine
     */
    bool isCharAt(std::string input, size_t position, char value) const;


    /*!
     *  Indique si un digit se trouve a la position donnee
     *  dans la chaine.
     *
     * \param input La chaine de caractere
     * \param position La position du digit
     * \return True si le digit se trouve bien a la position
     *  donnee. False sinon, ou si la position est en dehors de la chaine
     */
    bool isDigitAt(std::string input, size_t position) const;

};

#endif // FACTORYPOLYNOMIAL_H_INCLUDED
