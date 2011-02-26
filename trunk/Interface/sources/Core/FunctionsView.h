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
 *  \brief La classe FunctionsView est un contr�le englobant aussi bien la
 *  sc�ne graphique que les gestionnaires de fonction.
 *
 *  Cette classe permet de g�rer plusieurs fonctions et de leurs associer un
 *  gestionnaire. Les actions �mises par l'utilisateur sont g�rer par cette
 *  classe, comme par exemple, le d�placement de la sc�ne via la souris.
 *  Contrairement � la classe dont elle d�rive (QGraphicsView), cette classe ne
 *  permet pas � l'utilisateur de d�finir la sc�ne graphique. Ceci pour la
 *  protection des donn�es.
 */

class FunctionsView : public QGraphicsView
{
    Q_OBJECT

    public:

    /*! Enum�ration repr�sentant les modes d'affichage. */
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

    /*! Anticr�nelage */
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
     *  Affiche uniquement la fonction pass�e en param�tre et masque les
     *  autres.
     *
     *  \param functionManager Fonction � afficher
     */
    void showOnly(FunctionManager* functionManager);

    /*!
     *  Rafra�chit toutes les fonctions.
     *
     *  \note L'appel de cette m�thode invoque le calcul et le r�affichage de
     *  toutes les fonctions.
     */
    void refresh();

    /*!
     *  Retourne le gestionnaire de fonction associ� � l'expression.
     *
     *  \param function Expression de fonction
     *
     *  \return Gestionnaire de fonction
     */
    FunctionManager* getFunctionManager(IExpression* function) const;

    /*!
     *  Retourne le gestionnaire de fonction associ� � l'index.
     *
     *  \param index Index du gestionnaire de fonction
     *
     *  \return Gestionnaire de fonction
     */
    FunctionManager* getFunctionManager(int index) const;

    /*!
     *  Ajoute une fonction au contr�le. Cette m�thode cr�er un gestionnaire
     *  associ� � l'expression.
     *
     *  \param function Expression de fonction
     *
     *  \return Gestionnaire de fonction
     */
    FunctionManager* addFunction(IExpression* function);

    /*!
     *  Supprime le gestionnaire de fonction pass� en param�tre.
     *
     *  \param functionManager Gestionnaire de fonction
     *
     *  \return Vrai si la suppression est r�ussie, sinon faux
     */
    bool removeFunction(FunctionManager* functionManager);

    /*!
     *  Supprime le gestionnaire de fonction associ� � l'expression pass�e en
     *  param�tre.
     *
     *  \param function Expression de fonction
     *
     *  \return Vrai si la suppression est r�ussie, sinon faux
     */
    bool removeFunction(IExpression* function);

    /*!
     *  Supprime toutes les fonctions.
     */
    void clearFunctions();

    /*!
     *  Ajoute un marqueur � la sc�ne.
     *
     *  \param x Position en x
     *
     *  \return Index du marqueur
     */
    int addMarker(double x);

    /*!
     *  Supprime le marqueur associ� � l'index pass� en param�tre.
     *
     *  \param index Index du marqueur
     *
     *  \return Vrai si la suppression est r�ussie, sinon faux
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
     *  Passe le mode d'affichage dans celui pass� en argument.
     *
     *  \param displayMode Mode d'affichage
     */
    void switchOn(DisplayMode displayMode);

    /*!
     *  Indique si le marquage de la grille est activ�.
     *
     *  \return Vrai si le marquage de la grille est activ�, sinon faux
     */
    bool gridWithMarking() const;

    /*!
     *  Active ou d�sactive le marquage de la grille.
     *
     *  \param enabled Valeur d'activation
     */
    void setGridMarking(bool enabled);

    /*!
     *  Indique si l'anticr�nelage est activ�.
     *
     *  \return Vrai si l'anticr�nelage est activ�, sinon faux
     */
    bool isAntialiasied() const;

    /*!
     *  Active ou d�sactive l'anticr�nelage.
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
     *  Modifie la visibilit� de la position de la ligne de marquage x.
     *
     *  \param visible Visibilit�
     */
    void setXLineVisible(bool visible);

    /*!
     *  D�finit le rectangle de la sc�ne.
     *
     *  \param rect Rectangle de la sc�ne
     */
    void setSceneRect(const QRectF& rect);

    /*!
     *  D�finit le rectangle de la sc�ne.
     *
     *  \param x X
     *  \param y Y
     *  \param w Largeur
     *  \param h Hauteur
     */
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);



    public slots:

    /*!
     *  R�ceptionne le signal du minuteur "resizeTimer" quand le
     *  redimensionnement est termin�.
     */
    void resizeFinished();

    /*!
     *  R�ceptionne les signaux des �l�ments graphiques associ�s � la fonction.
     *
     *  \note Cette m�thode est utilis�e pour r�cup�rer les changements op�r�s
     *  directement par l'utilisateur sur les gestionnaires de fonction.
     *
     *  \param functionManager Gestionnaire de fonction
     */
    void functionItemModified(FunctionManager* functionManager);



    protected:

    /*!
     *  Zoom sur la sc�ne...
     *
     *  \note Cette m�thode s�curise les bornes.
     *
     *  \param centerPoint Centre du zoom
     *  \param xFactor Facteur x
     *  \param yFactor Facteur y
     */
    void zoom(const QPointF& centerPoint, double xFactor, double yFactor);

    /*!
     *  Supprime le gestionnaire de fonction associ� � l'index pass� en
     *  param�tre.
     *
     *  \param index Index du gestionnaire de fonction
     */
    void removeFunction(int index);

    /*!
     *  Retourne la sc�ne graphique.
     *
     *  \note Cette m�thode restreint son propre niveau d'acc�s.
     */
    QGraphicsScene* scene() const;

    /*!
     *  D�finit la sc�ne graphique.
     *
     *  \note Cette m�thode restreint son propre niveau d'acc�s.
     *
     *  \param scene Sc�ne graphique
     */
    void setScene(QGraphicsScene* scene);

    /*!
     *  Ev�nement du redimensionnement.
     *
     *  \param event Objet d'�v�nement
     */
    void resizeEvent(QResizeEvent* event);

    /*!
     *  Ev�nement du clic de la souris.
     *
     *  \param event Objet d'�v�nement
     */
    void mousePressEvent(QMouseEvent* event);

    /*!
     *  Ev�nement du double clic de la souris.
     *
     *  \param event Objet d'�v�nement
     */
    void mouseDoubleClickEvent(QMouseEvent* event);

    /*!
     *  Ev�nement du rel�chement du clic de la souris.
     *
     *  \param event Objet d'�v�nement
     */
    void mouseReleaseEvent(QMouseEvent* event);

    /*!
     *  Ev�nement des mouvements de la souris.
     *
     *  \param event Objet d'�v�nement
     */
    void mouseMoveEvent(QMouseEvent* event);

    /*!
     *  Ev�nement de la molette de la souris.
     *
     *  \param event Objet d'�v�nement
     */
    void wheelEvent(QWheelEvent* event);



    signals:

    /*!
     *  Signal �mis lorsque la sc�ne graphique est cliqu�e.
     *
     *  \param event Objet d'�v�nement
     *  \param point Point cliqu�
     */
    void clicked(QMouseEvent* event, const QPointF& point);

    /*!
     *  Signal �mis lorsque la sc�ne graphique est boug�e.
     *
     *  \param rect Rectangle de la sc�ne
     */
    void sceneMoved(const QRectF& rect);

    /*!
     *  Signal �mis lorsque la ligne de marquage est boug�e.
     *
     *  \param value Valeur de x
     */
    void xLineMoved(double value);
};

#endif // FUNCTIONS_VIEW_H
