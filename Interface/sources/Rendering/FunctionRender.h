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
 *  \brief La classe FunctionRender permet de repr�senter graphiquement une
 *  fonction.
 *
 *  Cette classe permet de calculer de mani�re pr�cise tous les points d'une
 *  fonction pour une sc�ne donn�e. Elle parvient aussi � d�terminer les
 *  discontinuit�s et de les repr�senter assez proprement...
 */

class FunctionRender : public FunctionGraphics
{
    private:

    /*! Profondeur maximale de la r�cursivit� */
    static const int MAX_DEPTH = 10;

    /*! Point hors �cran */
    static const double POINT_OFF_SCREEN = -1E9;

    /*! Delta utilis� pour d�terminer si un point est hors �cran */
    static const double POINT_OFF_SCREEN_DELTA = 1.0;

    /*! Trajectoire de la fonction */
    QPainterPath path;

    /*! Tableau de points, utilis� pour calculer la trajectoire finale */
    QVector<QPointF> points;

    /*! "Cases" utili�es pour d�tecter les fonctions discontinues */
    Cases cases1;

    /*! "Cases" utili�es pour d�tecter les fonctions discontinues */
    Cases cases2;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param scene Sc�ne graphique
     */
    FunctionRender(IExpression* function, QGraphicsScene* scene = NULL);

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
     *  Dessine la fonction. Cette m�thode est appel�e indirectement.
     *
     *  \note M�thode h�rit�e de QGraphicsItem.
     *
     *  \param painter Dispositif de dessin
     *  \param option Options de style
     *  \param widget Widget
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);



    private:

    /*!
     *  Instancie une nouvelle trajectoire � partir du tableau du tableau de
     *  points.
     *
     *  \note Appel�e � la fin de la m�thode "compute".
     */
    void createPath();

    /*!
     *  Indique si un point du tableau est � l'�cran.
     *
     *  \param index Index du tableau
     *
     *  \return Vrai si le point est � l'�cran, sinon faux
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
     *  R�sout les probl�mes de discontinuit�. Cette m�thode est appel�e
     *  lorsque l'une des deux �valuations est � l'�cran (ONSCREEN) et
     *  l'autre est au-dessus (ABOVE) ou en-dessous (BELOW) ou encore � l'�cran
     *  (ONSCREEN).
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param x1 Coordonn�e x1
     *  \param x2 Coordonn�e x2
     *  \param y1 Coordonn�e y1
     *  \param y2 Coordonn�e y2
     *  \param status1 Statut 1
     *  \param status2 Statut 2
     *  \param depth Profondeur de recherche
     */
    void discontinuity(QRectF* bounds, double x1, double x2, double y1, double y2, int status1, int status2, int depth);

    /*!
     *  Proc�de � une �valuation de domaine. Cette m�thode est appel�e lorsque
     *  l'un des deux statuts est non d�fini (UNDEFINED) et que l'autre est �
     *  l'�cran (ONSCREEN).
     *
     *  \note Cette m�thode ajoute dans tous les cas un point au tableau de
     *  points.
     *
     *  \param bounds Pointeur sur un rectangle contenant les bornes
     *  \param x1 Coordonn�e x1
     *  \param x2 Coordonn�e x2
     *  \param y1 Coordonn�e y1
     *  \param y2 Coordonn�e y2
     *  \param status1 Statut 1
     *  \param status2 Statut 2
     *  \param depth Profondeur de recherche
     */
    void domainEndpoint(QRectF* bounds, double x1, double x2, double y1, double y2, int status1, int status2, int depth);
};

#endif // FUNCTION_RENDER_H
