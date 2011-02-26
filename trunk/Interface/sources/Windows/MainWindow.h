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
 *  Fenêtre principale.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:

    /*! Enumération représentant une action utilisateur (opérations) */
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

    /*! Nombre maximum d'éléments pour une fonction */
    static const int MAX_FUNCTION_ITEMS = 30;

    /*! Borne x min par défaut */
    static const double DEFAULT_X_MIN = -20.0;

    /*! Borne x max par défaut */
    static const double DEFAULT_X_MAX = 20.0;

    /*! Borne y min par défaut */
    static const double DEFAULT_Y_MIN = -20.0;

    /*! Borne y max par défaut */
    static const double DEFAULT_Y_MAX = 20.0;

    /*! Caractère utilisé pour détecter les opérateurs fonctionnels */
    static const char OPERATOR_ARG_VAR = '#';

    /*! Fonction courante (managée) */
    FunctionManager* currentFonction;

    /*! Parseur de fonction */
    Parser parser;

    /*! Couleurs par défaut des fonctions */
    QColor functionsColors[MAX_FUNCTIONS];

    /*! Action courante de l'utilisateur */
    int currentAction;

    /*! Nombre de clics sur la scène (durant la création d'une opération) */
    int sceneClicks;

    /*! Prendre deux points (durant la création d'une opération) ? */
    bool takeTowPoints;

    /*! Borne x1 pour les opérations */
    double currentX1;

    /*! Borne x2 pour les opérations */
    double currentX2;

    /*! Position courante du curseur (edition de fonction) */
    int cursorPosition;

    /*! Sélection (edition de fonction) */
    QString selection;

    /* --------------------------------------------------------------------- */
    /* | Composants de base de la fenêtre                                  | */
    /* --------------------------------------------------------------------- */

    /*! Disposition principale */
    QHBoxLayout* mainLayout;

    /*! Cadre de contrôle */
    QFrame* controlFrame;

    /*! Groupement du rendu */
    QGroupBox* renderBox;

    /* --------------------------------------------------------------------- */
    /* | Cadre de contrôle                                                 | */
    /* --------------------------------------------------------------------- */

    /*! Disposition du cadre de contrôle */
    QVBoxLayout* controlLayout;

    /*! Groupement d'édition */
    QGroupBox* editionBox;

    /*! Disposition de la boîte d'édition */
    QVBoxLayout* editionBoxLayout;

    /*! Disposition pour la zone d'édition et le bouton de fonction */
    QHBoxLayout* editionRowLayout;

    /*! Ligne d'édition de fonction */
    QLineEdit* functionLineEdit;

    /*! Bouton de création de fonction */
    QPushButton* createFunctionButton;

    /*! Cadre des opérateurs */
    QFrame* operatorsFrame;

    /*! Grillage des opérateurs */
    QGridLayout* operatorsGrid;

    /*! Groupement des fonctions */
    QGroupBox* functionBox;

    /*! Disposition des contrôles de la fonction */
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

    /*! Ligne des opérations de fonction */
    QHBoxLayout* operationsRowLayout;

    /*! Bouton de création d'intégrale */
    QPushButton* integralButton;

    /*! Bouton de création de tangente */
    QPushButton* tangentButton;

    /*! Bouton de recherche du zéro */
    QPushButton* zeroButton;

    /*! Bouton de recherche du maximum */
    QPushButton* maximumButton;

    /*! Bouton de recherche du minimum */
    QPushButton* minimumButton;

    /*! Table de résultats */
    QTableWidget* resultsTable;

    /*! Ligne de résultats */
    QHBoxLayout* resultsRowLayout;

    /*! Bouton de suppression d'une opération */
    QPushButton* deleteOperationButton;

    /*! Bouton de suppression de toutes les opérations */
    QPushButton* clearOperationsButton;

    /* --------------------------------------------------------------------- */
    /* | Rendu                                                             | */
    /* --------------------------------------------------------------------- */

    /*! Disposition du rendu */
    QVBoxLayout* renderBoxLayout;

    /*! En-tête du rendu (bornes...) */
    QHBoxLayout* renderHeaderLayout;

    /*! Case à cocher pour l'affichage unique */
    QCheckBox* onlyOneCheckBox;

    /*! Modificateur de bornes : x min */
    QDoubleSpinBox* xMinSpinBox;

    /*! Modificateur de bornes : x max */
    QDoubleSpinBox* xMaxSpinBox;

    /*! Modificateur de bornes : y min */
    QDoubleSpinBox* yMinSpinBox;

    /*! Modificateur de bornes : y max */
    QDoubleSpinBox* yMaxSpinBox;

    /*! Bouton de réinitialisation des bornes */
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

    /*! Action : Réinitialiser les bornes */
    QAction* resetBoundsAction;

    /*! Action : Changer la couleur de la fonction */
    QAction* changeFunctionColorAction;

    /*! Action : Supprimer la fonction */
    QAction* deleteFunctionAction;

    /*! Action : Supprimer toutes les fonctions */
    QAction* clearFunctionsAction;

    /*! Action : Créer une intégrale */
    QAction* integralAction;

    /*! Action : Créer une tangente */
    QAction* tangentAction;

    /*! Action : Chercher un zéro */
    QAction* zeroAction;

    /*! Action : Chercher un maximum */
    QAction* maximumAction;

    /*! Action : Chercher un minimum */
    QAction* minimumAction;

    /*! Action : Supprimer l'opération sélectionné */
    QAction* deleteOperationAction;

    /*! Action : Supprimer toutes les opérations */
    QAction* clearOperationsAction;

    /*! Action : Affichage exclusif */
    QAction* onlyOneAction;

    /*! Action : Afficher la grille */
    QAction* viewGridAction;

    /*! Action : Anticrénelage */
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

    /*! Menu "Opérations" */
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
     *  Réceptionne le signal de la liste de fonctions "functionsComboBox" et
     *  récupère la fonction associée.
     */
    void functionSelected(int index);

    /*!
     *  Réceptionne le signal du bouton "createFunctionButton" et tente de
     *  créer la fonction entrée par l'utilisateur.
     */
    void insertFunction();

    /*!
     *  Réceptionne le signal du bouton "functionColorButton" et modifie la
     *  couleur de la fonction associée.
     */
    void changeFunctionColor();

    /*!
     *  Réceptionne le signal du bouton "deleteFunctionButton" et supprime la
     *  fonction associée.
     */
    void deleteFonction();

    /*!
     *  Réceptionne le signal de l'action "clearFunctionsAction" et supprime
     *  toutes les fonctions associées.
     */
    void clearFunctions();

    /*!
     *  Réceptionne le signal du bouton "integralButton" et lance la création
     *  d'une intégrale.
     *
     *  \param enabled Valeur d'activation
     */
    void doIntegral(bool enabled);

    /*!
     *  Réceptionne le signal du bouton "tangentButton" et lance la création
     *  d'une tangente.
     *
     *  \param enabled Valeur d'activation
     */
    void doTangent(bool enabled);

    /*!
     *  Réceptionne le signal du bouton "zeroButton" et lance la recherche d'un
     *  zéro.
     *
     *  \param enabled Valeur d'activation
     */
    void doZero(bool enabled);

    /*!
     *  Réceptionne le signal du bouton "maximumButton" et lance la recherche
     *  d'un maximum.
     *
     *  \param enabled Valeur d'activation
     */
    void doMaximum(bool enabled);

    /*!
     *  Réceptionne le signal du bouton "minimumButton" et lance la recherche
     *  d'un minimum.
     *
     *  \param enabled Valeur d'activation
     */
    void doMinimum(bool enabled);

    /*!
     *  Réceptionne le signal du bouton "deleteOperationButton" et supprime
     *  l'élément graphique de la fonction associée.
     */
    void deleteFunctionItem();

    /*!
     *  Réceptionne le signal du bouton "clearOperationsButton" et supprime
     *  tous les éléments graphique de la fonction associée.
     */
    void clearFunctionItems();

    /*!
     *  Réceptionne le signal de la ligne d'édition "functionLineEdit" et
     *  examine son état.
     *
     *  \param text Texte de la ligne d'édition
     */
    void functionEdited(QString text);

    /*!
     *  Réceptionne le signal de la ligne d'édition "functionLineEdit" et
     *  enregistre la position du curseur.
     *
     *  \param oldPosition Ancienne position
     *  \param newPosition Nouvelle position
     */
    void storeCursorPosition(int oldPosition, int newPosition);

    /*!
     *  Réceptionne le signal de la ligne d'édition "functionLineEdit" et
     *  enregistre la sélection.
     */
    void storeSelection();

    /*!
     *  Réceptionne le signal des boutons opérateurs et insère le tag associé.
     *
     *  \param tag Tag
     */
    void insertOperator(QString tag);

    /*!
     *  Réceptionne le signal de la case à cocher "onlyOneCheckBox" et
     *  détermine le mode d'affichage.
     *
     *  \param onlyOne Affichage exclusif
     */
    void changeDisplayMode(bool onlyOne);

    /*!
     *  Réceptionne le signal de l'action "viewGridAction" et détermine si la
     *  grille doit être affichée.
     *
     *  \param enabled Valeur d'activation
     */
    void setGridMarking(bool enabled);

    /*!
     *  Réceptionne le signal de l'action "antialiasingAction" et détermine si
     *  l'anticrénelage doit être activé.
     *
     *  \param enabled Valeur d'activation
     */
    void setAntialiasing(bool enabled);

    /*!
     *  Réceptionne le signal de la FunctionsView et traite le clic.
     *
     *  \param event Evénement
     *  \param point Point cliqué sur la scène
     */
    void sceneClicked(QMouseEvent* event, const QPointF& point);

    /*!
     *  Réceptionne le signal des modificateurs de bornes.
     */
    void boundsChanged();

    /*!
     *  Réceptionne le signal de la FunctionsView et traite la mouvement de la
     *  scène.
     *
     *  \param rect Rectangle de la scène
     */
    void boundsMoved(const QRectF& rect);

    /*!
     *  Réceptionne le signal du bouton "resetBoundsButton" et réinitialise les
     *  bornes.
     */
    void reinitializeBounds();

    /*!
     *  Réceptionne le signal de la FunctionsView et traite la mouvement de la
     *  ligne x.
     *
     *  \param value Coordonnée x
     */
    void xLineMoved(double value);

    /*!
     *  Réceptionne le signal de changement des contrôles XPositionBar.
     *
     *  \param value Coordonnée x
     */
    void xPositionChanged(double value);

    /*!
     *  Réceptionne le signal d'acceptation des contrôles XPositionBar.
     *
     *  \param value Coordonnée x
     */
    void xPositionAccepted(double value);

    /*!
     *  Réceptionne le signal d'annulation des contrôles XPositionBar.
     */
    void xPositionAborted();

    /*!
     *  Réceptionne le signal de l'action "helpAction" et affiche l'aide.
     */
    void showHelp();

    /*!
     *  Réceptionne le signal de l'action "aboutAction" et affiche la boîte
     *  "A propos de ..."
     */
    void showAboutBox();



    private:

    /*!
     *  Créer la structure principale.
     */
    void createMainStructure();

    /*!
     *  Créer le panneau de contrôle.
     */
    void createControlPanel();

    /*!
     *  Créer la boîte d'édition.
     */
    void createEditionBox();

    /*!
     *  Créer boîte de fonctions.
     */
    void createFunctionsBox();

    /*!
     *  Créer le panneau du rendu graphique.
     */
    void createRenderPanel();

    /*!
     *  Créer les actions.
     */
    void createActions();

    /*!
     *  Créer le menu.
     */
    void createMenu();

    /*!
     *  Créer un élément graphique de fonction et l'associe avec la fonction
     *  courante.
     */
    void createFunctionItem();

    /*!
     *  Créer un bouton opérateur.
     *
     *  \param text Texte du bouton
     *  \param tag Tag du bouton
     */
    void createOperatorButton(const QString& text, const QString& tag);

    /*!
     *  Créer un modificateur de borne.
     *
     *  \param spinBox Modificateur à instancier
     *  \param title Titre
     *  \param value Valeur
     *  \param min Valeur minimum
     *  \param max Valeur maximum
     */
    void createBoundSetter(QDoubleSpinBox*& spinBox, const QString& title, int value, int min, int max);

    /*!
     *  Exécute une action.
     */
    void doAction(bool enabled);

    /*!
     *  Contrôle l'état de la fonction.
     */
    void checkFunctionState();

    /*!
     *  Réinitialise la table de résultat.
     */
    void clearResultTable();

    /*!
     *  Rafraîchis la table de résultat.
     */
    void refreshResultTable();

    /*!
     *  Active ou désactive les boutons.
     *
     *  \param enabled Valeur d'activation
     *  \param except Exception
     */
    void setAllButtons(bool enabled, QPushButton* except = NULL);

    /*!
     *  Active ou désactive les boutons d'opérations.
     *
     *  \param enabled Valeur d'activation
     */
    void setOperationsButtons(bool enabled);
};

#endif // MAIN_WINDOW_H
