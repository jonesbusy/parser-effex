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
 *  \brief La classe SurfaceRender permet de repr�senter graphiquement une
 *  surface.
 *
 *  Cette classe dessine une surface entre deux bornes d'une fonction (par
 *  exemple : dans le cas d'une int�grale). Elle g�re aussi un effet de d�grad�
 *  li� � la couleur de l'instance.
 */

class SurfaceRender : public FunctionItem
{
    private:

    /*! Surface */
    QPolygonF surface;

    /*! D�grad� */
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
     *  \param data Donn�es de l'�l�ment graphique
     *  \param scene Sc�ne graphique
     */
    SurfaceRender(IExpression* function, double x1, double x2, const ItemData& data, QGraphicsScene* scene = NULL);

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
     *  D�finit la couleur du graphique.
     *
     *  \note Cette red�finition permet de prendre en compte le d�grad�.
     *
     *  \param color Couleur du graphique et du d�grad�
     */
    void setColor(const QColor& color);

    /*!
     *  Retourne un rectangle repr�sentant la zone � dessiner.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \return Rectangle repr�sentant la zone � dessiner
     */
    QRectF boundingRect() const;

    /*!
     *  Dessine la surface. Cette m�thode est appel�e indirectement.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // SURFACE_RENDER_H
