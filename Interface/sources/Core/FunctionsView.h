#ifndef FUNCTIONS_VIEW_H
#define FUNCTIONS_VIEW_H

/*!
 *  \file FunctionsView.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 2.0
 */

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QVector>
#include <QTimer>
#include <QPoint>
#include <QPointF>
#include <QLineF>
#include <QRectF>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include "Core/FunctionManager.h"
#include "Rendering/Grid.h"
#include "Expression/IExpression.h"

/*!
 *  \class FunctionsView
 *
 *  \brief La classe FunctionsView est un contrôle englobant aussi bien la
 *  scène graphique que les gestionnaires de fonction.
 *
 *  Cette classe permet de gérer plusieurs fonctions et de leurs associer un
 *  gestionnaire. Les actions émises par l'utilisateur sont gérer par cette
 *  classe, comme par exemple, le déplacement de la scène via la souris.
 *  Contrairement à la classe dont elle dérive (QGraphicsView), cette classe ne
 *  permet pas à l'utilisateur de définir la scène graphique. Ceci pour la
 *  protection des données.
 */

class FunctionsView : public QGraphicsView
{
    Q_OBJECT

    public:

    /*! Enumération représentant les modes d'affichage. */
    enum DisplayMode
    {
        FreeLook    = 0,
        Fixed       = 1
    };

    /*! Valeur minimum en x */
    static const int X_MIN_LIMIT = -300;

    /*! Valeur maximum en x */
    static const int X_MAX_LIMIT = 300;

    /*! Valeur minimum en y */
    static const int Y_MIN_LIMIT = -300;

    /*! Valeur maximum en y */
    static const int Y_MAX_LIMIT = 300;



    private:

    /*! Fonctions */
    QVector<FunctionManager*> functions;

    /*! Marqueurs d'image */
    QVector<QGraphicsLineItem*> markers;

    /*! Grillage */
    Grid* grid;

    /*! Ligne de marquage en x */
    QGraphicsLineItem* xLine;

    /*! Rectangle de zoom */
    QGraphicsRectItem* zoomRect;

    /*! Mode d'affichage */
    DisplayMode displayMode;

    /*! Pinceau des marqueurs */
    QPen markerPen;

    /*! Sauvegarde du bouton de la souris */
    Qt::MouseButton mouseButtonPressed;

    /*! Point d'agrippement pour la souris */
    QPoint mouseGrab;

    /*! Anticrénelage */
    bool antialiasing;

    /*! En mouvement... */
    bool isMoving;

    /*! Minuteur de redimensionnement */
    QTimer* resizeTimer;



    public:

    /*!
     *  Constructeur
     *
     *  \param xMin Valeur minimum en x
     *  \param xMax Valeur maximum en x
     *  \param yMin Valeur minimum en y
     *  \param yMax Valeur maximum en y
     *  \param parent QObject parent
     */
    FunctionsView(double xMin, double xMax, double yMin, double yMax, QWidget* parent = NULL);

    /*!
     *  Destructeur
     */
    ~FunctionsView();

    /*!
     *  Affiche toutes les fonctions...
     */
    void showAll();

    /*!
     *  Affiche uniquement la fonction passée en paramètre et masque les
     *  autres.
     *
     *  \param functionManager Fonction à afficher
     */
    void showOnly(FunctionManager* functionManager);

    /*!
     *  Rafraîchit toutes les fonctions.
     *
     *  \note L'appel de cette méthode invoque le calcul et le réaffichage de
     *  toutes les fonctions.
     */
    void refresh();

    /*!
     *  Retourne le gestionnaire de fonction associé à l'expression.
     *
     *  \param function Expression de fonction
     *
     *  \return Gestionnaire de fonction
     */
    FunctionManager* getFunctionManager(IExpression* function) const;

    /*!
     *  Retourne le gestionnaire de fonction associé à l'index.
     *
     *  \param index Index du gestionnaire de fonction
     *
     *  \return Gestionnaire de fonction
     */
    FunctionManager* getFunctionManager(int index) const;

    /*!
     *  Ajoute une fonction au contrôle. Cette méthode créer un gestionnaire
     *  associé à l'expression.
     *
     *  \param function Expression de fonction
     *
     *  \return Gestionnaire de fonction
     */
    FunctionManager* addFunction(IExpression* function);

    /*!
     *  Supprime le gestionnaire de fonction passé en paramètre.
     *
     *  \param functionManager Gestionnaire de fonction
     *
     *  \return Vrai si la suppression est réussie, sinon faux
     */
    bool removeFunction(FunctionManager* functionManager);

    /*!
     *  Supprime le gestionnaire de fonction associé à l'expression passée en
     *  paramètre.
     *
     *  \param function Expression de fonction
     *
     *  \return Vrai si la suppression est réussie, sinon faux
     */
    bool removeFunction(IExpression* function);

    /*!
     *  Supprime toutes les fonctions.
     */
    void clearFunctions();

    /*!
     *  Ajoute un marqueur à la scène.
     *
     *  \param x Position en x
     *
     *  \return Index du marqueur
     */
    int addMarker(double x);

    /*!
     *  Supprime le marqueur associé à l'index passé en paramètre.
     *
     *  \param index Index du marqueur
     *
     *  \return Vrai si la suppression est réussie, sinon faux
     */
    bool removeMarker(int index);

    /*!
     *  Supprime tous les marqueurs.
     */
    void clearMarkers();

    /*!
     *  Retourne le mode d'affichage.
     *
     *  \return Mode d'affichage
     */
    int getDisplayMode() const;

    /*!
     *  Passe le mode d'affichage dans celui passé en argument.
     *
     *  \param displayMode Mode d'affichage
     */
    void switchOn(DisplayMode displayMode);

    /*!
     *  Indique si le marquage de la grille est activé.
     *
     *  \return Vrai si le marquage de la grille est activé, sinon faux
     */
    bool gridWithMarking() const;

    /*!
     *  Active ou désactive le marquage de la grille.
     *
     *  \param enabled Valeur d'activation
     */
    void setGridMarking(bool enabled);

    /*!
     *  Indique si l'anticrénelage est activé.
     *
     *  \return Vrai si l'anticrénelage est activé, sinon faux
     */
    bool isAntialiasied() const;

    /*!
     *  Active ou désactive l'anticrénelage.
     *
     *  \param enabled Valeur d'activation
     */
    void setAntialiasing(bool enabled);

    /*!
     *  Modifie la position de la ligne de marquage x.
     *
     *  \param x Nouvelle position
     */
    void setXLine(double x);

    /*!
     *  Indique si la ligne de marquage x est visible.
     *
     *  \return Vrai si la ligne de marquage x est visible, sinon faux
     */
    bool xLineIsVisible() const;

    /*!
     *  Modifie la visibilité de la position de la ligne de marquage x.
     *
     *  \param visible Visibilité
     */
    void setXLineVisible(bool visible);

    /*!
     *  Définit le rectangle de la scène.
     *
     *  \param rect Rectangle de la scène
     */
    void setSceneRect(const QRectF& rect);

    /*!
     *  Définit le rectangle de la scène.
     *
     *  \param x X
     *  \param y Y
     *  \param w Largeur
     *  \param h Hauteur
     */
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);



    public slots:

    /*!
     *  Réceptionne le signal du minuteur "resizeTimer" quand le
     *  redimensionnement est terminé.
     */
    void resizeFinished();

    /*!
     *  Réceptionne les signaux des éléments graphiques associés à la fonction.
     *
     *  \note Cette méthode est utilisée pour récupérer les changements opérés
     *  directement par l'utilisateur sur les gestionnaires de fonction.
     *
     *  \param functionManager Gestionnaire de fonction
     */
    void functionItemModified(FunctionManager* functionManager);



    protected:

    /*!
     *  Zoom sur la scène...
     *
     *  \note Cette méthode sécurise les bornes.
     *
     *  \param centerPoint Centre du zoom
     *  \param xFactor Facteur x
     *  \param yFactor Facteur y
     */
    void zoom(const QPointF& centerPoint, double xFactor, double yFactor);

    /*!
     *  Supprime le gestionnaire de fonction associé à l'index passé en
     *  paramètre.
     *
     *  \param index Index du gestionnaire de fonction
     */
    void removeFunction(int index);

    /*!
     *  Retourne la scène graphique.
     *
     *  \note Cette méthode restreint son propre niveau d'accès.
     */
    QGraphicsScene* scene() const;

    /*!
     *  Définit la scène graphique.
     *
     *  \note Cette méthode restreint son propre niveau d'accès.
     *
     *  \param scene Scène graphique
     */
    void setScene(QGraphicsScene* scene);

    /*!
     *  Evénement du redimensionnement.
     *
     *  \param event Objet d'événement
     */
    void resizeEvent(QResizeEvent* event);

    /*!
     *  Evénement du clic de la souris.
     *
     *  \param event Objet d'événement
     */
    void mousePressEvent(QMouseEvent* event);

    /*!
     *  Evénement du double clic de la souris.
     *
     *  \param event Objet d'événement
     */
    void mouseDoubleClickEvent(QMouseEvent* event);

    /*!
     *  Evénement du relâchement du clic de la souris.
     *
     *  \param event Objet d'événement
     */
    void mouseReleaseEvent(QMouseEvent* event);

    /*!
     *  Evénement des mouvements de la souris.
     *
     *  \param event Objet d'événement
     */
    void mouseMoveEvent(QMouseEvent* event);

    /*!
     *  Evénement de la molette de la souris.
     *
     *  \param event Objet d'événement
     */
    void wheelEvent(QWheelEvent* event);



    signals:

    /*!
     *  Signal émis lorsque la scène graphique est cliquée.
     *
     *  \param event Objet d'événement
     *  \param point Point cliqué
     */
    void clicked(QMouseEvent* event, const QPointF& point);

    /*!
     *  Signal émis lorsque la scène graphique est bougée.
     *
     *  \param rect Rectangle de la scène
     */
    void sceneMoved(const QRectF& rect);

    /*!
     *  Signal émis lorsque la ligne de marquage est bougée.
     *
     *  \param value Valeur de x
     */
    void xLineMoved(double value);
};

#endif // FUNCTIONS_VIEW_H
