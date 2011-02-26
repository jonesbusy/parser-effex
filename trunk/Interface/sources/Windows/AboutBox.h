#ifndef ABOUT_BOX_H
#define ABOUT_BOX_H

/*!
 *  \file AboutBox.h
 *  \author David Miserez
 *  \date 26.05.2010
 *  \version 1.0
 */

#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QKeyEvent>

/*!
 *  \class AboutBox
 *
 *  Cette classe affiche une fenêtre "A propos de Effex".
 */

class AboutBox : public QDialog
{
    Q_OBJECT

    private:

    /*! Bannière */
    QLabel* banner;

    /*! No comment */
    QLabel* easterEggs;

    /*! No comment */
    QLabel* kiki;

    /*! Texte */
    QLabel* text;

    /*! Bouton valider */
    QPushButton* closeButton;



    public:

    /*!
     *  Constructeur
     *
     *  \param parent Parent
     */
    AboutBox(QWidget* parent = NULL);



    protected:

    /*!
     *  Evénement clavier.
     *
     *  \param event Evénement
     */
    void keyPressEvent(QKeyEvent* event);
};

#endif // ABOUT_BOX_H
