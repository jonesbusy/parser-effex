#ifndef FUNCTION_ITEM_H
#define FUNCTION_ITEM_H

/*!
 *  \file FunctionItem.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 1.1
 */

#include <QGraphicsScene>

#include "Rendering/FunctionGraphics.h"
#include "Expression/IExpression.h"
#include "Data/ItemData.h"

/*!
 *  \class FunctionItem
 *
 *  \brief La classe FunctionItem représente un élément graphique associé à une
 *  fonction.
 *
 *  Cette classe abstraite factorise les élément graphiques d'une fonction en
 *  leurs associant des données.
 */

class FunctionItem : public FunctionGraphics
{
    private:

    /*! Données de l'élément graphique */
    ItemData data;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param data Données de l'élément graphique
     *  \param scene Scène graphique
     */
    FunctionItem(IExpression* function, const ItemData& data, QGraphicsScene* scene = NULL);

    /*!
     *  Retourne les données de l'élément graphique.
     *
     *  \return Données de l'élément graphique
     */
    const ItemData& getData() const;
};

#endif // FUNCTION_ITEM_H
