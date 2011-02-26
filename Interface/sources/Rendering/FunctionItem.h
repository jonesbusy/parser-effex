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
 *  \brief La classe FunctionItem repr�sente un �l�ment graphique associ� � une
 *  fonction.
 *
 *  Cette classe abstraite factorise les �l�ment graphiques d'une fonction en
 *  leurs associant des donn�es.
 */

class FunctionItem : public FunctionGraphics
{
    private:

    /*! Donn�es de l'�l�ment graphique */
    ItemData data;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param data Donn�es de l'�l�ment graphique
     *  \param scene Sc�ne graphique
     */
    FunctionItem(IExpression* function, const ItemData& data, QGraphicsScene* scene = NULL);

    /*!
     *  Retourne les donn�es de l'�l�ment graphique.
     *
     *  \return Donn�es de l'�l�ment graphique
     */
    const ItemData& getData() const;
};

#endif // FUNCTION_ITEM_H
