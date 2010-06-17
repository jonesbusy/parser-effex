#ifndef CASES_H_INCLUDED
#define CASES_H_INCLUDED

/**
 * \file Cases.h
 * \author Valentin Delaye
 * \author Pascal Berberat
 * \version 1.0
 * \date 12.05.2010
 *
 * Permet d'aider les plotters a dessiner correctement les fonctions
 * discontinues. Lors des differentes operations susceptibles de creer
 * une discontinuite (asympote verticale), le case est rempli des valeurs
 * suivante :
 * (-1 si l'evaluation est negative, 1 si positive et
 * 0 si l'evaluation vaut 0)
 *
 * Exemple : 1 / (x - 2) pour une evaluation de -3 a 3
 * par pas de 1. Pour le denominateur, le case
 * contiendra [-1, -1, -1, -1, 0, 1].
 *
 * Le case est utilise pour les operations suivantes :
 * - Division
 * - Tangeante
 * - Valeur absolue
 *
 * Par defaut, le case est NULL.
 */

#include <vector>

#include "ExpressionExport.h"

/*! \class Cases
 *
 * Classe permetant d'aider a detecter les discontinuites
 */
class DLL_EXPORT Cases
{
    private:

    /*! Les differents cases. */
    std::vector<int> cases;



    public:

    /*!
     *  Ajoute un nouveau case dans la liste
     *
     *  \param value Valeur a ajouter dans le case
     */
    void add(int value);

    /*!
     *  Vide le case et toutes les valeurs ajoutees
     *  a l'aide de la methode add(int).
     */
    void clear();

    /*!
     *  Permet de comparer deux cases.
     *
     *  \param c Case a comparer avec l'objet courant
     *  \return True si les deux cases sont egaut, false sinon
     */
    bool equals(const Cases& c) const;

    /*!
     *  Operateur == . Permet de comparer deux cases.
     *
     *  \param c1 Premier case
     *  \param c2 Deuxieme case
     *  \return True si les deux cases sont egaux, false sinon
     */
    friend bool operator == (const Cases& c1, const Cases& c2);

};

#endif // CASES_H_INCLUDED
