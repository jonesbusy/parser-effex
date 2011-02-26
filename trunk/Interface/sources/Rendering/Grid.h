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
 *  \brief La classe Grid repr�sente un grillage pour fonction.
 *
 *  Cette classe permet de dessiner un grillage sur n'importe quelle sc�ne.
 */

class Grid : public QGraphicsItem
{
    private:

    /*! Pinceau des axes */
    QPen axesPen;

    /*! Pinceau des lignes */
    QPen linesPen;

    /*! Utilis� pour indiquer s'il faut ou non dessiner le marquage */
    bool marking;

    /*! Indique si le mode de marquage est en train d'�tre modifi� */
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
     *  Active ou d�sactive le marquage.
     *
     *  \param enabled Activer
     */
    void setMarking(bool enabled);

    /*!
     *  Retourne un rectangle repr�sentant la zone � dessiner.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \return Rectangle repr�sentant la zone � dessiner
     */
    QRectF boundingRect() const;

    /*!
     *  Dessine le grillage. Cette m�thode est appel�e indirectement.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // GRID_H
