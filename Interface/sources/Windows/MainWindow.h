#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/*!
 *  \file MainWindow.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 1.2
 */

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QTableWidgetItem>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QColorDialog>
#include <QVariant>
#include <QString>
#include <QFont>
#include <QKeySequence>
#include <QSizePolicy>
#include <QPointF>
#include <QRectF>
#include <QColor>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>

#include "Core/FunctionsView.h"
#include "Core/FunctionManager.h"
#include "Data/ItemData.h"
#include "UserControls/CalcButton.h"
#include "UserControls/XPositionBar.h"
#include "Windows/AboutBox.h"
#include "Parser/Parser.h"
#include "Expression/IExpression.h"

/*!
 *  \class MainWindow
 *
 *  Fen�tre principale.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:

    /*! Enum�ration repr�sentant une action utilisateur (op�rations) */
    enum Action
    {
        NONE        = 0,
        INTEGRAL    = 1,
        TANGENT     = 2,
        ZERO        = 3,
        MAXIMUM     = 4,
        MINIMUM     = 5
    };

    /*! Nombre maximum de fonctions */
    static const int MAX_FUNCTIONS = 5;

    /*! Nombre maximum d'�l�ments pour une fonction */
    static const int MAX_FUNCTION_ITEMS = 30;

    /*! Borne x min par d�faut */
    static const double DEFAULT_X_MIN = -20.0;

    /*! Borne x max par d�faut */
    static const double DEFAULT_X_MAX = 20.0;

    /*! Borne y min par d�faut */
    static const double DEFAULT_Y_MIN = -20.0;

    /*! Borne y max par d�faut */
    static const double DEFAULT_Y_MAX = 20.0;

    /*! Caract�re utilis� pour d�tecter les op�rateurs fonctionnels */
    static const char OPERATOR_ARG_VAR = '#';

    /*! Fonction courante (manag�e) */
    FunctionManager* currentFonction;

    /*! Parseur de fonction */
    Parser parser;

    /*! Couleurs par d�faut des fonctions */
    QColor functionsColors[MAX_FUNCTIONS];

    /*! Action courante de l'utilisateur */
    int currentAction;

    /*! Nombre de clics sur la sc�ne (durant la cr�ation d'une op�ration) */
    int sceneClicks;

    /*! Prendre deux points (durant la cr�ation d'une op�ration) ? */
    bool takeTowPoints;

    /*! Borne x1 pour les op�rations */
    double currentX1;

    /*! Borne x2 pour les op�rations */
    double currentX2;

    /*! Position courante du curseur (edition de fonction) */
    int cursorPosition;

    /*! S�lection (edition de fonction) */
    QString selection;

    /* --------------------------------------------------------------------- */
    /* | Composants de base de la fen�tre                                  | */
    /* --------------------------------------------------------------------- */

    /*! Disposition principale */
    QHBoxLayout* mainLayout;

    /*! Cadre de contr�le */
    QFrame* controlFrame;

    /*! Groupement du rendu */
    QGroupBox* renderBox;

    /* --------------------------------------------------------------------- */
    /* | Cadre de contr�le                                                 | */
    /* --------------------------------------------------------------------- */

    /*! Disposition du cadre de contr�le */
    QVBoxLayout* controlLayout;

    /*! Groupement d'�dition */
    QGroupBox* editionBox;

    /*! Disposition de la bo�te d'�dition */
    QVBoxLayout* editionBoxLayout;

    /*! Disposition pour la zone d'�dition et le bouton de fonction */
    QHBoxLayout* editionRowLayout;

    /*! Ligne d'�dition de fonction */
    QLineEdit* functionLineEdit;

    /*! Bouton de cr�ation de fonction */
    QPushButton* createFunctionButton;

    /*! Cadre des op�rateurs */
    QFrame* operatorsFrame;

    /*! Grillage des op�rateurs */
    QGridLayout* operatorsGrid;

    /*! Groupement des fonctions */
    QGroupBox* functionBox;

    /*! Disposition des contr�les de la fonction */
    QVBoxLayout* functionBoxLayout;

    /*! Cadre du choix des fonctions */
    QFrame* functionsRowFrame;

    /*! Ligne du choix des fonctions */
    QHBoxLayout* functionsRowLayout;

    /*! Liste des fonctions */
    QComboBox* functionsComboBox;

    /*! Bouton de changement de couleur pour fonction */
    QPushButton* functionColorButton;

    /*! Bouton de suppression de fonction */
    QPushButton* deleteFunctionButton;

    /*! Ligne des op�rations de fonction */
    QHBoxLayout* operationsRowLayout;

    /*! Bouton de cr�ation d'int�grale */
    QPushButton* integralButton;

    /*! Bouton de cr�ation de tangente */
    QPushButton* tangentButton;

    /*! Bouton de recherche du z�ro */
    QPushButton* zeroButton;

    /*! Bouton de recherche du maximum */
    QPushButton* maximumButton;

    /*! Bouton de recherche du minimum */
    QPushButton* minimumButton;

    /*! Table de r�sultats */
    QTableWidget* resultsTable;

    /*! Ligne de r�sultats */
    QHBoxLayout* resultsRowLayout;

    /*! Bouton de suppression d'une op�ration */
    QPushButton* deleteOperationButton;

    /*! Bouton de suppression de toutes les op�rations */
    QPushButton* clearOperationsButton;

    /* --------------------------------------------------------------------- */
    /* | Rendu                                                             | */
    /* --------------------------------------------------------------------- */

    /*! Disposition du rendu */
    QVBoxLayout* renderBoxLayout;

    /*! En-t�te du rendu (bornes...) */
    QHBoxLayout* renderHeaderLayout;

    /*! Case � cocher pour l'affichage unique */
    QCheckBox* onlyOneCheckBox;

    /*! Modificateur de bornes : x min */
    QDoubleSpinBox* xMinSpinBox;

    /*! Modificateur de bornes : x max */
    QDoubleSpinBox* xMaxSpinBox;

    /*! Modificateur de bornes : y min */
    QDoubleSpinBox* yMinSpinBox;

    /*! Modificateur de bornes : y max */
    QDoubleSpinBox* yMaxSpinBox;

    /*! Bouton de r�initialisation des bornes */
    QPushButton* resetBoundsButton;

    /*! Gestionnaire de rendu de fonctions */
    FunctionsView* functionsView;

    /*! Barre de positionnement courante... */
    XPositionBar* xPositionBar;

    /*! Barre de positionnement 1 */
    XPositionBar* xPositionBar1;

    /*! Barre de positionnement 2 */
    XPositionBar* xPositionBar2;

    /* --------------------------------------------------------------------- */
    /* | Actions                                                           | */
    /* --------------------------------------------------------------------- */

    /*! Action : Fermer l'application */
    QAction* closeAction;

    /*! Action : R�initialiser les bornes */
    QAction* resetBoundsAction;

    /*! Action : Changer la couleur de la fonction */
    QAction* changeFunctionColorAction;

    /*! Action : Supprimer la fonction */
    QAction* deleteFunctionAction;

    /*! Action : Supprimer toutes les fonctions */
    QAction* clearFunctionsAction;

    /*! Action : Cr�er une int�grale */
    QAction* integralAction;

    /*! Action : Cr�er une tangente */
    QAction* tangentAction;

    /*! Action : Chercher un z�ro */
    QAction* zeroAction;

    /*! Action : Chercher un maximum */
    QAction* maximumAction;

    /*! Action : Chercher un minimum */
    QAction* minimumAction;

    /*! Action : Supprimer l'op�ration s�lectionn� */
    QAction* deleteOperationAction;

    /*! Action : Supprimer toutes les op�rations */
    QAction* clearOperationsAction;

    /*! Action : Affichage exclusif */
    QAction* onlyOneAction;

    /*! Action : Afficher la grille */
    QAction* viewGridAction;

    /*! Action : Anticr�nelage */
    QAction* antialiasingAction;

    /*! Action : Afficher l'aide */
    QAction* helpAction;

    /*! Action : A propos de Effex */
    QAction* aboutAction;

    /* --------------------------------------------------------------------- */
    /* | Menu                                                              | */
    /* --------------------------------------------------------------------- */

    /*! Barre de menu */
    QMenuBar* menuBar;

    /*! Menu "Fichier" */
    QMenu* fileMenu;

    /*! Menu "Edition" */
    QMenu* editionMenu;

    /*! Menu "Fonctions" */
    QMenu* functionsMenu;

    /*! Menu "Op�rations" */
    QMenu* operationsMenu;

    /*! Menu "Affichage" */
    QMenu* displayMenu;

    /*! Menu "Aide" */
    QMenu* helpMenu;



    public:

    /*!
     *  Constructeur
     */
    MainWindow();



    public slots:

    /*!
     *  R�ceptionne le signal de la liste de fonctions "functionsComboBox" et
     *  r�cup�re la fonction associ�e.
     */
    void functionSelected(int index);

    /*!
     *  R�ceptionne le signal du bouton "createFunctionButton" et tente de
     *  cr�er la fonction entr�e par l'utilisateur.
     */
    void insertFunction();

    /*!
     *  R�ceptionne le signal du bouton "functionColorButton" et modifie la
     *  couleur de la fonction associ�e.
     */
    void changeFunctionColor();

    /*!
     *  R�ceptionne le signal du bouton "deleteFunctionButton" et supprime la
     *  fonction associ�e.
     */
    void deleteFonction();

    /*!
     *  R�ceptionne le signal de l'action "clearFunctionsAction" et supprime
     *  toutes les fonctions associ�es.
     */
    void clearFunctions();

    /*!
     *  R�ceptionne le signal du bouton "integralButton" et lance la cr�ation
     *  d'une int�grale.
     *
     *  \param enabled Valeur d'activation
     */
    void doIntegral(bool enabled);

    /*!
     *  R�ceptionne le signal du bouton "tangentButton" et lance la cr�ation
     *  d'une tangente.
     *
     *  \param enabled Valeur d'activation
     */
    void doTangent(bool enabled);

    /*!
     *  R�ceptionne le signal du bouton "zeroButton" et lance la recherche d'un
     *  z�ro.
     *
     *  \param enabled Valeur d'activation
     */
    void doZero(bool enabled);

    /*!
     *  R�ceptionne le signal du bouton "maximumButton" et lance la recherche
     *  d'un maximum.
     *
     *  \param enabled Valeur d'activation
     */
    void doMaximum(bool enabled);

    /*!
     *  R�ceptionne le signal du bouton "minimumButton" et lance la recherche
     *  d'un minimum.
     *
     *  \param enabled Valeur d'activation
     */
    void doMinimum(bool enabled);

    /*!
     *  R�ceptionne le signal du bouton "deleteOperationButton" et supprime
     *  l'�l�ment graphique de la fonction associ�e.
     */
    void deleteFunctionItem();

    /*!
     *  R�ceptionne le signal du bouton "clearOperationsButton" et supprime
     *  tous les �l�ments graphique de la fonction associ�e.
     */
    void clearFunctionItems();

    /*!
     *  R�ceptionne le signal de la ligne d'�dition "functionLineEdit" et
     *  examine son �tat.
     *
     *  \param text Texte de la ligne d'�dition
     */
    void functionEdited(QString text);

    /*!
     *  R�ceptionne le signal de la ligne d'�dition "functionLineEdit" et
     *  enregistre la position du curseur.
     *
     *  \param oldPosition Ancienne position
     *  \param newPosition Nouvelle position
     */
    void storeCursorPosition(int oldPosition, int newPosition);

    /*!
     *  R�ceptionne le signal de la ligne d'�dition "functionLineEdit" et
     *  enregistre la s�lection.
     */
    void storeSelection();

    /*!
     *  R�ceptionne le signal des boutons op�rateurs et ins�re le tag associ�.
     *
     *  \param tag Tag
     */
    void insertOperator(QString tag);

    /*!
     *  R�ceptionne le signal de la case � cocher "onlyOneCheckBox" et
     *  d�termine le mode d'affichage.
     *
     *  \param onlyOne Affichage exclusif
     */
    void changeDisplayMode(bool onlyOne);

    /*!
     *  R�ceptionne le signal de l'action "viewGridAction" et d�termine si la
     *  grille doit �tre affich�e.
     *
     *  \param enabled Valeur d'activation
     */
    void setGridMarking(bool enabled);

    /*!
     *  R�ceptionne le signal de l'action "antialiasingAction" et d�termine si
     *  l'anticr�nelage doit �tre activ�.
     *
     *  \param enabled Valeur d'activation
     */
    void setAntialiasing(bool enabled);

    /*!
     *  R�ceptionne le signal de la FunctionsView et traite le clic.
     *
     *  \param event Ev�nement
     *  \param point Point cliqu� sur la sc�ne
     */
    void sceneClicked(QMouseEvent* event, const QPointF& point);

    /*!
     *  R�ceptionne le signal des modificateurs de bornes.
     */
    void boundsChanged();

    /*!
     *  R�ceptionne le signal de la FunctionsView et traite la mouvement de la
     *  sc�ne.
     *
     *  \param rect Rectangle de la sc�ne
     */
    void boundsMoved(const QRectF& rect);

    /*!
     *  R�ceptionne le signal du bouton "resetBoundsButton" et r�initialise les
     *  bornes.
     */
    void reinitializeBounds();

    /*!
     *  R�ceptionne le signal de la FunctionsView et traite la mouvement de la
     *  ligne x.
     *
     *  \param value Coordonn�e x
     */
    void xLineMoved(double value);

    /*!
     *  R�ceptionne le signal de changement des contr�les XPositionBar.
     *
     *  \param value Coordonn�e x
     */
    void xPositionChanged(double value);

    /*!
     *  R�ceptionne le signal d'acceptation des contr�les XPositionBar.
     *
     *  \param value Coordonn�e x
     */
    void xPositionAccepted(double value);

    /*!
     *  R�ceptionne le signal d'annulation des contr�les XPositionBar.
     */
    void xPositionAborted();

    /*!
     *  R�ceptionne le signal de l'action "helpAction" et affiche l'aide.
     */
    void showHelp();

    /*!
     *  R�ceptionne le signal de l'action "aboutAction" et affiche la bo�te
     *  "A propos de ..."
     */
    void showAboutBox();



    private:

    /*!
     *  Cr�er la structure principale.
     */
    void createMainStructure();

    /*!
     *  Cr�er le panneau de contr�le.
     */
    void createControlPanel();

    /*!
     *  Cr�er la bo�te d'�dition.
     */
    void createEditionBox();

    /*!
     *  Cr�er bo�te de fonctions.
     */
    void createFunctionsBox();

    /*!
     *  Cr�er le panneau du rendu graphique.
     */
    void createRenderPanel();

    /*!
     *  Cr�er les actions.
     */
    void createActions();

    /*!
     *  Cr�er le menu.
     */
    void createMenu();

    /*!
     *  Cr�er un �l�ment graphique de fonction et l'associe avec la fonction
     *  courante.
     */
    void createFunctionItem();

    /*!
     *  Cr�er un bouton op�rateur.
     *
     *  \param text Texte du bouton
     *  \param tag Tag du bouton
     */
    void createOperatorButton(const QString& text, const QString& tag);

    /*!
     *  Cr�er un modificateur de borne.
     *
     *  \param spinBox Modificateur � instancier
     *  \param title Titre
     *  \param value Valeur
     *  \param min Valeur minimum
     *  \param max Valeur maximum
     */
    void createBoundSetter(QDoubleSpinBox*& spinBox, const QString& title, int value, int min, int max);

    /*!
     *  Ex�cute une action.
     */
    void doAction(bool enabled);

    /*!
     *  Contr�le l'�tat de la fonction.
     */
    void checkFunctionState();

    /*!
     *  R�initialise la table de r�sultat.
     */
    void clearResultTable();

    /*!
     *  Rafra�chis la table de r�sultat.
     */
    void refreshResultTable();

    /*!
     *  Active ou d�sactive les boutons.
     *
     *  \param enabled Valeur d'activation
     *  \param except Exception
     */
    void setAllButtons(bool enabled, QPushButton* except = NULL);

    /*!
     *  Active ou d�sactive les boutons d'op�rations.
     *
     *  \param enabled Valeur d'activation
     */
    void setOperationsButtons(bool enabled);
};

#endif // MAIN_WINDOW_H
