#ifndef TANGENT_RENDER_H
#define TANGENT_RENDER_H

/*!
 *  \file TangentRender.h
 *  \author Pascal Berberat
 *  \date 19.05.2010
 *  \version 1.0
 */

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QLineF>
#include <QRectF>
#include <QPen>

#include "Rendering/FunctionItem.h"
#include "Expression/IExpression.h"
#include "Data/ItemData.h"
#include "Data/MathTools.h"

/*!
 *  \class TangentRender
 *
 *  \brief La classe TangentRender permet de repr�senter graphiquement une
 *  tangente.
 *
 *  Cette classe dessine une tangente li�e � une fonction.
 */

class TangentRender : public FunctionItem
{
    private:

    /*! Trac� de la tangente */
    QLineF line;

    /*! Coordonn�e x */
    double x;

    /*! Valeur de la tangente */
    double tangent;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param x Coordonn�e x
     *  \param tangent Valeur de la tangente
     *  \param data Donn�es de l'�l�ment graphique
     *  \param scene Sc�ne graphique
     */
    TangentRender(IExpression* function, double x, double tangent, const ItemData& data, QGraphicsScene* scene = NULL);

    /*!
     *  M�thode de calcul, elle sera appel�e � chaque fois que la sc�ne est
     *  modifi�e.
     *
     *  \note M�thode h�rit�e de FunctionGraphics.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param accuracy Niveau de d�tails
     */
    void compute(QRectF* bounds, int accuracy);

    /*!
     *  Retourne un rectangle repr�sentant la zone � dessiner.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \return Rectangle repr�sentant la zone � dessiner
     */
    QRectF boundingRect() const;

    /*!
     *  Dessine la tangente. Cette m�thode est appel�e indirectement.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // TANGENT_RENDER_H
