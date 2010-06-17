#ifndef FACTORYNAMEDFUNCTION_H_INCLUDED
#define FACTORYNAMEDFUNCTION_H_INCLUDED

/*!
 *  \file FactoryNamedFunction.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 10.03.2010
 *
 *  Permettre de fabriquer des fonction nommees.
 */

#include <map>
#include <string>
#include <exception>
#include <cmath>

#include "NamedFunction.h"
#include "IFactoryFunction.h"

/*! \class FactoryNamedFunction
 *
 *  Fabrique concrete de fonction nommees. Permet de fabriquer
 *  des objets NamedFunction.
 */
class FactoryNamedFunction : public IFactoryFunction
{
    private :

    /*! Permet de faire la correspondance entre le nom de la fonction
     *  et la fonction elle-meme.
     */
    std::map<std::string, double(*)(double)> functions;



    public :

    /*!
     * Constructeur. Permet de creer la nouvelle fabrique.
     */
    FactoryNamedFunction();

    /*!
     * Destructeur.
     */
    virtual ~FactoryNamedFunction();

    /*!
     *  Permet de retourner une instance d'une fonction
     *  suivant une chaine de caractere representant le nom de
     *  la fonction.
     *
     *  \param name Le nom de la fonction.
     *  \return L'instance du polynome ou null si impossible
     *  de creer la fonction.
     */
    NamedFunction* getInstance(std::string name) const;

};

#endif // FACTORYNAMEDFUNCTION_H_INCLUDED
