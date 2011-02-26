#ifndef FUNCTION_GRAPHICS_H
#define FUNCTION_GRAPHICS_H

/*!
 *  \file FunctionGraphics.h
 *  \author Pascal Berberat
 *  \date 28.04.2010
 *  \version 1.2
 */

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QColor>
#include <QPen>

#include "Expression/IExpression.h"
#include "Expression/Cases.h"
#include "Data/MathTools.h"

/*!
 *  \class FunctionGraphics
 *
 *  \brief La classe FunctionGraphics est la classe de base de tous les rendus
 *  graphique d'une fonction.
 *
 *  Cette classe abstraite est la classe de base de tous les rendus d'une
 *  fonction (elle-m�me comprise). Elle encapsule une expression fonctionnelle
 *  et propose des m�thodes utiles pour la d�tection de d�passement de bornes
 *  ou de limites. Les classes h�rit�es devront impl�menter la m�thode de
 *  calcul "compute" et les deux m�thodes de dessin "paint" et "boundingRect".
 */

class FunctionGraphics : public QGraphicsItem
{
    private:

    /*! Fonction */
    IExpression* function;

    /*! Couleur */
    QColor color;

    /*! Plume */
    QPen pen;

    /*! Valeur utilis�e pour les d�passements de y */
    double yDelta;



    protected:

    /*! Enum�ration utilis�e pour repr�senter le statut d'un point. */
    enum PointStatus
    {
        UNDEFINED   = 0,
        ONSCREEN    = 1,
        ABOVE       = 2,
        BELOW       = 3
    };

    /*! Pr�cision de calcul pour yDelta. */
    static const int Y_DELTA_ACCURACY = 200;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param scene Sc�ne graphique
     */
    FunctionGraphics(IExpression* function, QGraphicsScene* scene = NULL);

    /*!
     *  M�thode abstraite de calcul, elle sera appel�e � chaque fois que la
     *  sc�ne est modifi�e.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param accuracy Niveau de d�tails
     */
    virtual void compute(QRectF* bounds, int accuracy) = 0;

    /*!
     *  Retourne la couleur du graphique.
     *
     *  \return Couleur du graphique
     */
    const QColor& getColor() const;

    /*!
     *  D�finit la couleur du graphique.
     *
     *  \param color Couleur du graphique
     */
    virtual void setColor(const QColor& color);

    /*!
     *  Optimise le rectangle contenant les bornes pour l'affichage.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     */
    static void optimizeBounds(QRectF* bounds);



    protected:

    /*!
     *  Evalue la valeur x et retourne le r�sultat y. Si le r�sultat d�passe
     *  les bornes, le d�passement sera limit� � +/- yDelta.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param x Valeur de x
     *  \param cases Object qui peut �tre utilis� pour d�terminer si la
     *  fonction contient des zones discontinues
     *
     *  \return Valeur y
     */
    double eval(QRectF* bounds, double x, Cases* cases = NULL) const;

    /*!
     *  Retourne le code du statut de y.
     *
     *  \note Se r�f�rer � l'�num�ration "PointStatus".
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param y Valeur de y
     *
     *  \return Code du statut de y
     */
    int getStatus(QRectF* bounds, double y) const;

    /*!
     *  Invoque un rafra�chissement d'affichage.
     *
     *  \note Equivalent � QGraphicsItem::update(this->boundingRect()).
     *
     *  \return Couleur du graphique
     */
    void update();

    /*!
     *  Retourne la plume.
     *
     *  \return Plume
     */
    const QPen& getPen() const;

    /*!
     *  D�finit la plume.
     *
     *  \param pen Plume
     */
    void setPen(const QPen& pen);

    /*!
     *  Retourne le delta de y.
     *
     *  \return Delta de y
     */
    double getYDelta() const;

    /*!
     *  D�finit le delta de y par rapport aux bornes.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     */
    void setYDelta(QRectF* bounds);
};

#endif // FUNCTION_GRAPHICS_H
