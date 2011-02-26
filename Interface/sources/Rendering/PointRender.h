#ifndef POINT_RENDER_H
#define POINT_RENDER_H

/*!
 *  \file PointRender.h
 *  \author Pascal Berberat
 *  \date 14.05.2010
 *  \version 1.0
 */

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPointF>
#include <QRectF>
#include <QPen>

#include "Rendering/FunctionItem.h"
#include "Expression/IExpression.h"
#include "Data/ItemData.h"
#include "Data/MathTools.h"

/*!
 *  \class PointRender
 *
 *  \brief La classe PointRender permet de repr�senter graphiquement un point.
 *
 *  Cette classe dessine une ellipse autour d'un point li� � une fonction.
 */

class PointRender : public FunctionItem
{
    private:

    /*! Point */
    QPointF point;

    /*! Coordonn�e x */
    double x;

    /*! Largeur */
    double width;

    /*! Hauteur */
    double height;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param x Coordonn�e x
     *  \param data Donn�es de l'�l�ment graphique
     *  \param scene Sc�ne graphique
     */
    PointRender(IExpression* function, double x, const ItemData& data, QGraphicsScene* scene = NULL);

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
     *  Dessine le point. Cette m�thode est appel�e indirectement.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // POINT_RENDER_H
