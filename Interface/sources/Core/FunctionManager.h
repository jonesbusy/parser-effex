#ifndef FUNCTION_MANAGER_H
#define FUNCTION_MANAGER_H

/*!
 *  \file FunctionGraphics.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 1.2
 */

#include <QObject>
#include <QGraphicsScene>
#include <QVector>
#include <QString>
#include <QRectF>
#include <QColor>

#include <cmath>

#include "Expression/IExpression.h"
#include "Data/ItemData.h"
#include "Data/MathTools.h"
#include "Rendering/FunctionGraphics.h"
#include "Rendering/FunctionRender.h"
#include "Rendering/FunctionItem.h"
#include "Rendering/PointRender.h"
#include "Rendering/SurfaceRender.h"
#include "Rendering/TangentRender.h"

/*!
 *  \class FunctionManager
 *
 *  \brief La classe FunctionManager est un gestionnaire pour une fonction...
 *
 *  Cette classe permet de g�rer une fonction et d'y associer des �l�ments
 *  graphiques. On peut ajouter � une fonction des �l�ments tels que des
 *  int�grales, des tangentes, des z�ros, des maximum ou des minimums. Elle
 *  g�re �galement la couleur et la visibilit� de la fonction ainsi que les
 *  �l�ments associ�s.
 */

class FunctionManager : public QObject
{
    Q_OBJECT

    private:

    /*! Fonction */
    IExpression* function;

    /*! Sc�ne graphique */
    QGraphicsScene* scene;

    /*! Rendu de la fonction */
    FunctionRender functionRender;

    /*! El�ments associ�s � la fonction */
    QVector<FunctionItem*> items;

    /*! Profondeur de dessin */
    int zValue;

    /*! Profondeur */
    static int currentZValue;



    public:

    /*!
     *  Constructeur
     *
     *  \param function Fonction
     *  \param scene Sc�ne graphique
     */
    FunctionManager(IExpression* function, QGraphicsScene* scene);

    /*!
     *  Destructeur
     */
    ~FunctionManager();

    /*!
     *  Met � jour la fonction et les �l�ments associ�s.
     *
     *  \param accuracy Niveau de d�tails
     */
    void update(int accuracy);

    /*!
     *  Ajoute une int�grale.
     *
     *  \param name Nom de l'int�grale
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'�l�ment graphique
     */
    int addIntegral(const QString& name, double x1, double x2);

    /*!
     *  Ajoute une tangente.
     *
     *  \param name Nom de la tangente
     *  \param x Borne "x"
     *
     *  \return Identifiant de l'�l�ment graphique
     */
    int addTangent(const QString& name, double x);

    /*!
     *  Ajoute un z�ro.
     *
     *  \param name Nom du z�ro
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'�l�ment graphique
     */
    int addZero(const QString& name, double x1, double x2);

    /*!
     *  Ajoute un maximum.
     *
     *  \param name Nom du maximum
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'�l�ment graphique
     */
    int addMaximum(const QString& name, double x1, double x2);

    /*!
     *  Ajoute un minimum.
     *
     *  \param name Nom du minimum
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'�l�ment graphique
     */
    int addMinimum(const QString& name, double x1, double x2);

    /*!
     *  Supprime un �l�ment graphique.
     *
     *  \param index Identifiant de l'�l�ment graphique
     *
     *  \return Vrai si la suppression est r�ussie, sinon faux
     */
    bool removeItem(int index);

    /*!
     *  Supprime tous les �l�ments graphique.
     */
    void clearItems();

    /*!
     *  D�termine si la fonction est la m�me que celle contenue dans l'objet.
     *
     *  \param function Fonction � comparer
     *
     *  \return Vrai si la fonction est la m�me que celle contenue dans
     *  l'objet, sinon faux
     */
    bool equals(IExpression* function) const;

    /*!
     *  Retourne le nombre d'�l�ments graphiques.
     *
     *  \return Nombre d'�l�ments graphiques
     */
    int countItems() const;

    /*!
     *  Retourne les donn�es de l'�l�ment graphique.
     *
     *  \param index Identifiant de l'�l�ment graphique
     *
     *  \return Donn�es de l'�l�ment graphique
     */
    ItemData getItemData(int index) const;

    /*!
     *  Retourne la couleur.
     *
     *  \return Couleur
     */
    const QColor& getColor() const;

    /*!
     *  D�finit la couleur.
     *
     *  \param color Couleur
     */
    void setColor(const QColor& color);

    /*!
     *  Indique si l'objet est visible.
     *
     *  \return Vrai si visible, sinon faux
     */
    bool isVisible() const;

    /*!
     *  D�finit si l'objet est visible.
     *
     *  \param visible Visible
     */
    void setVisible(bool visible);

    /*!
     *  Retourne la valeur courante de la profondeur.
     *
     *  \return Valeur courante de la profondeur
     */
    static int getCurrentZValue();



    private:

    /*!
     *  Ajoute un �l�ment graphique associ� � la fonction.
     *
     *  \param item El�ment graphique
     *
     *  \return Identifiant de l'�l�ment graphique
     */
    int addItem(FunctionItem* item);

    /*!
     *  G�n�re le domaine de d�finition.
     *
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Domaine de d�finition
     */
    QString generateDomain(double x1, double x2) const;



    signals:

    /*!
     *  Signal �mis lorsqu'un �l�ment graphique est ajout�.
     *
     *  \param functionManager Instance
     */
    void itemAdded(FunctionManager* functionManager);

    /*!
     *  Signal �mis lorsqu'un �l�ment graphique est supprim�.
     *
     *  \param functionManager Instance
     */
    void itemRemoved(FunctionManager* functionManager);
};

#endif // FUNCTION_MANAGER_H
