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
 *  \brief La classe PointRender permet de représenter graphiquement un point.
 *
 *  Cette classe dessine une ellipse autour d'un point lié à une fonction.
 */

class PointRender : public FunctionItem
{
    private:

    /*! Point */
    QPointF point;

    /*! Coordonnée x */
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
     *  \param x Coordonnée x
     *  \param data Données de l'élément graphique
     *  \param scene Scène graphique
     */
    PointRender(IExpression* function, double x, const ItemData& data, QGraphicsScene* scene = NULL);

    /*!
     *  Méthode de calcul, elle sera appelée à chaque fois que la scène est
     *  modifiée.
     *
     *  \note Méthode héritée de FunctionGraphics.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param accuracy Niveau de détails
     */
    void compute(QRectF* bounds, int accuracy);

    /*!
     *  Retourne un rectangle représentant la zone à dessiner.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \return Rectangle représentant la zone à dessiner
     */
    QRectF boundingRect() const;

    /*!
     *  Dessine le point. Cette méthode est appelée indirectement.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // POINT_RENDER_H
