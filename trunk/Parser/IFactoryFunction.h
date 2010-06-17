#ifndef FACTORYFUNCTION_H_INCLUDED
#define FACTORYFUNCTION_H_INCLUDED

/*!
 *  \file IFactoryFunction.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 03.03.2010
 *
 *  Permet de fournir une interface commune pour creer les
 *  differents types de fonction.
 */

#include <string>

#include "AbstractFunction.h"

/*! \class IFactoryFunction
 *
 *  Fabrique abstraite.
 */
class IFactoryFunction
{
    public :

    /*!
     *  Permet de retourner une instance d'une fonction abstraite
     *  suivant une chaine de caractere representant la fonction.
     *
     *  \param name Le nom de la fonction
     *  \return L'instance de la fonction ou null si impossible
     *  de creer la fonction.
     */
    virtual AbstractFunction* getInstance(std::string name) const = 0;

};


#endif // FACTORYFUNCTION_H_INCLUDED
