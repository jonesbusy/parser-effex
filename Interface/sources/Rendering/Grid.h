#ifndef GRID_H
#define GRID_H

/*!
 *  \file Grid.h
 *  \author David Miserez
 *  \date 17.05.2010
 *  \version 1.1
 */

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include <QPen>

/*!
 *  \class Grid
 *
 *  \brief La classe Grid représente un grillage pour fonction.
 *
 *  Cette classe permet de dessiner un grillage sur n'importe quelle scène.
 */

class Grid : public QGraphicsItem
{
    private:

    /*! Pinceau des axes */
    QPen axesPen;

    /*! Pinceau des lignes */
    QPen linesPen;

    /*! Utilisé pour indiquer s'il faut ou non dessiner le marquage */
    bool marking;

    /*! Indique si le mode de marquage est en train d'être modifié */
    bool markingIsChanging;



    public:

    /*!
     *  Constructeur
     */
    Grid();

    /*!
     *  Indique si le marquage est actif ou non.
     *
     *  \return Vrai si le marquage est actif, sinon faux
     */
    bool getMarking() const;

    /*!
     *  Active ou désactive le marquage.
     *
     *  \param enabled Activer
     */
    void setMarking(bool enabled);

    /*!
     *  Retourne un rectangle représentant la zone à dessiner.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \return Rectangle représentant la zone à dessiner
     */
    QRectF boundingRect() const;

    /*!
     *  Dessine le grillage. Cette méthode est appelée indirectement.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // GRID_H
