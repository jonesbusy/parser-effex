#ifndef FUNCTION_RENDER_H
#define FUNCTION_RENDER_H

/*!
 *  \file FunctionRender.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 3.0
 */

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
#include <QVector>
#include <QPointF>
#include <QRectF>
#include <QPen>

#include "Rendering/FunctionGraphics.h"
#include "Expression/IExpression.h"
#include "Expression/Cases.h"

/*!
 *  \class FunctionRender
 *
 *  \brief La classe FunctionRender permet de représenter graphiquement une
 *  fonction.
 *
 *  Cette classe permet de calculer de manière précise tous les points d'une
 *  fonction pour une scène donnée. Elle parvient aussi à déterminer les
 *  discontinuités et de les représenter assez proprement...
 */

class FunctionRender : public FunctionGraphics
{
    private:

    /*! Profondeur maximale de la récursivité */
    static const int MAX_DEPTH = 10;

    /*! Point hors écran */
    static const double POINT_OFF_SCREEN = -1E9;

    /*! Delta utilisé pour déterminer si un point est hors écran */
    static const double POINT_OFF_SCREEN_DELTA = 1.0;

    /*! Trajectoire de la fonction */
    QPainterPath path;

    /*! Tableau de points, utilisé pour calculer la trajectoire finale */
    QVector<QPointF> points;

    /*! "Cases" utiliées pour détecter les fonctions discontinues */
    Cases cases1;

    /*! "Cases" utiliées pour détecter les fonctions discontinues */
    Cases cases2;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param scene Scène graphique
     */
    FunctionRender(IExpression* function, QGraphicsScene* scene = NULL);

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
     *  Dessine la fonction. Cette méthode est appelée indirectement.
     *
     *  \note Méthode héritée de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);



    private:

    /*!
     *  Instancie une nouvelle trajectoire à partir du tableau du tableau de
     *  points.
     *
     *  \note Appelée à la fin de la méthode "compute".
     */
    void createPath();

    /*!
     *  Indique si un point du tableau est à l'écran.
     *
     *  \param index Index du tableau
     *
     *  \return Vrai si le point est à l'écran, sinon faux
     */
    bool isOnScreen(int index) const;

    /*!
     *  Indique si un point est dessinable.
     *
     *  \param value Valeur du point
     *
     *  \return Vrai si le point est dessinable, sinon faux
     */
    bool isDrawable(double value) const;

    /*!
     *  Résout les problèmes de discontinuité. Cette méthode est appelée
     *  lorsque l'une des deux évaluations est à l'écran (ONSCREEN) et
     *  l'autre est au-dessus (ABOVE) ou en-dessous (BELOW) ou encore à l'écran
     *  (ONSCREEN).
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param x1 Coordonnée x1
     *  \param x2 Coordonnée x2
     *  \param y1 Coordonnée y1
     *  \param y2 Coordonnée y2
     *  \param status1 Statut 1
     *  \param status2 Statut 2
     *  \param depth Profondeur de recherche
     */
    void discontinuity(QRectF* bounds, double x1, double x2, double y1, double y2, int status1, int status2, int depth);

    /*!
     *  Procède à une évaluation de domaine. Cette méthode est appelée lorsque
     *  l'un des deux statuts est non défini (UNDEFINED) et que l'autre est à
     *  l'écran (ONSCREEN).
     *
     *  \note Cette méthode ajoute dans tous les cas un point au tableau de
     *  points.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param x1 Coordonnée x1
     *  \param x2 Coordonnée x2
     *  \param y1 Coordonnée y1
     *  \param y2 Coordonnée y2
     *  \param status1 Statut 1
     *  \param status2 Statut 2
     *  \param depth Profondeur de recherche
     */
    void domainEndpoint(QRectF* bounds, double x1, double x2, double y1, double y2, int status1, int status2, int depth);
};

#endif // FUNCTION_RENDER_H
