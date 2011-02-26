#ifndef SURFACE_RENDER_H
#define SURFACE_RENDER_H

/*!
 *  \file SurfaceRender.h
 *  \author Pascal Berberat
 *  \date 04.05.2010
 *  \version 1.2
 */

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QLinearGradient>
#include <QGraphicsOpacityEffect>
#include <QVector>
#include <QPolygonF>
#include <QPointF>
#include <QRectF>
#include <QColor>
#include <QPen>

#include "Rendering/FunctionItem.h"
#include "Data/ItemData.h"
#include "Expression/IExpression.h"

/*!
 *  \class SurfaceRender
 *
 *  \brief La classe SurfaceRender permet de représenter graphiquement une
 *  surface.
 *
 *  Cette classe dessine une surface entre deux bornes d'une fonction (par
 *  exemple : dans le cas d'une intégrale). Elle gère aussi un effet de dégradé
 *  lié à la couleur de l'instance.
 */

class SurfaceRender : public FunctionItem
{
    private:

    /*! Surface */
    QPolygonF surface;

    /*! Dégradé */
    QLinearGradient gradient;

    /*! Borne x1 */
    double x1;

    /*! Borne x2 */
    double x2;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param x1 Borne x1
     *  \param x2 Borne x2
     *  \param data Données de l'élément graphique
     *  \param scene Scène graphique
     */
    SurfaceRender(IExpression* function, double x1, double x2, const ItemData& data, QGraphicsScene* scene = NULL);

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
     *  Définit la couleur du graphique.
     *
     *  \note Cette redéfinition permet de prendre en compte le dégradé.
     *
     *  \param color Couleur du graphique et du dégradé
     */
    void setColor(const QColor& color);

    /*!
     *  Retourne un rectangle représentant la zone à dessiner.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \return Rectangle représentant la zone à dessiner
     */
    QRectF boundingRect() const;

    /*!
     *  Dessine la surface. Cette méthode est appelée indirectement.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // SURFACE_RENDER_H
