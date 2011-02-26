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
 *  Cette classe permet de gérer une fonction et d'y associer des éléments
 *  graphiques. On peut ajouter à une fonction des éléments tels que des
 *  intégrales, des tangentes, des zéros, des maximum ou des minimums. Elle
 *  gère également la couleur et la visibilité de la fonction ainsi que les
 *  éléments associés.
 */

class FunctionManager : public QObject
{
    Q_OBJECT

    private:

    /*! Fonction */
    IExpression* function;

    /*! Scène graphique */
    QGraphicsScene* scene;

    /*! Rendu de la fonction */
    FunctionRender functionRender;

    /*! Eléments associés à la fonction */
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
     *  \param scene Scène graphique
     */
    FunctionManager(IExpression* function, QGraphicsScene* scene);

    /*!
     *  Destructeur
     */
    ~FunctionManager();

    /*!
     *  Met à jour la fonction et les éléments associés.
     *
     *  \param accuracy Niveau de détails
     */
    void update(int accuracy);

    /*!
     *  Ajoute une intégrale.
     *
     *  \param name Nom de l'intégrale
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'élément graphique
     */
    int addIntegral(const QString& name, double x1, double x2);

    /*!
     *  Ajoute une tangente.
     *
     *  \param name Nom de la tangente
     *  \param x Borne "x"
     *
     *  \return Identifiant de l'élément graphique
     */
    int addTangent(const QString& name, double x);

    /*!
     *  Ajoute un zéro.
     *
     *  \param name Nom du zéro
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'élément graphique
     */
    int addZero(const QString& name, double x1, double x2);

    /*!
     *  Ajoute un maximum.
     *
     *  \param name Nom du maximum
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'élément graphique
     */
    int addMaximum(const QString& name, double x1, double x2);

    /*!
     *  Ajoute un minimum.
     *
     *  \param name Nom du minimum
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Identifiant de l'élément graphique
     */
    int addMinimum(const QString& name, double x1, double x2);

    /*!
     *  Supprime un élément graphique.
     *
     *  \param index Identifiant de l'élément graphique
     *
     *  \return Vrai si la suppression est réussie, sinon faux
     */
    bool removeItem(int index);

    /*!
     *  Supprime tous les éléments graphique.
     */
    void clearItems();

    /*!
     *  Détermine si la fonction est la même que celle contenue dans l'objet.
     *
     *  \param function Fonction à comparer
     *
     *  \return Vrai si la fonction est la même que celle contenue dans
     *  l'objet, sinon faux
     */
    bool equals(IExpression* function) const;

    /*!
     *  Retourne le nombre d'éléments graphiques.
     *
     *  \return Nombre d'éléments graphiques
     */
    int countItems() const;

    /*!
     *  Retourne les données de l'élément graphique.
     *
     *  \param index Identifiant de l'élément graphique
     *
     *  \return Données de l'élément graphique
     */
    ItemData getItemData(int index) const;

    /*!
     *  Retourne la couleur.
     *
     *  \return Couleur
     */
    const QColor& getColor() const;

    /*!
     *  Définit la couleur.
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
     *  Définit si l'objet est visible.
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
     *  Ajoute un élément graphique associé à la fonction.
     *
     *  \param item Elément graphique
     *
     *  \return Identifiant de l'élément graphique
     */
    int addItem(FunctionItem* item);

    /*!
     *  Génère le domaine de définition.
     *
     *  \param x1 Borne "x1"
     *  \param x2 Borne "x2"
     *
     *  \return Domaine de définition
     */
    QString generateDomain(double x1, double x2) const;



    signals:

    /*!
     *  Signal émis lorsqu'un élément graphique est ajouté.
     *
     *  \param functionManager Instance
     */
    void itemAdded(FunctionManager* functionManager);

    /*!
     *  Signal émis lorsqu'un élément graphique est supprimé.
     *
     *  \param functionManager Instance
     */
    void itemRemoved(FunctionManager* functionManager);
};

#endif // FUNCTION_MANAGER_H
