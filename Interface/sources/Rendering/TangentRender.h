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
 *  \brief La classe TangentRender permet de représenter graphiquement une
 *  tangente.
 *
 *  Cette classe dessine une tangente liée à une fonction.
 */

class TangentRender : public FunctionItem
{
    private:

    /*! Tracé de la tangente */
    QLineF line;

    /*! Coordonnée x */
    double x;

    /*! Valeur de la tangente */
    double tangent;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param x Coordonnée x
     *  \param tangent Valeur de la tangente
     *  \param data Données de l'élément graphique
     *  \param scene Scène graphique
     */
    TangentRender(IExpression* function, double x, double tangent, const ItemData& data, QGraphicsScene* scene = NULL);

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
     *  Dessine la tangente. Cette méthode est appelée indirectement.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // TANGENT_RENDER_H
