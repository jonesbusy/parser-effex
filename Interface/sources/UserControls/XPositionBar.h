#ifndef X_POSITION_BAR_H
#define X_POSITION_BAR_H

/*!
 *  \file XPositionBar.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 1.1
 */

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QScrollBar>
#include <QPushButton>
#include <QSizePolicy>
#include <QKeySequence>
#include <QString>
#include <QKeyEvent>

/*!
 *  \class XPositionBar
 *
 *  La classe XPositionBar est un contrôle personnalisé qui permet de choisir
 *  une valeur de x dans un domaine fini.
 */

class XPositionBar : public QFrame
{
    Q_OBJECT

    private:

    /*! Echelle de la barre de défilement */
    static const int PARTS = 500;

    /*! Disposition globale */
    QHBoxLayout* layout;

    /*! Label */
    QLabel* label;

    /*! Valeur numérique */
    QDoubleSpinBox* spinBox;

    /*! Barre de défilement */
    QScrollBar* scrollBar;

    /*! Bouton */
    QPushButton* acceptButton;



    public:

    /*!
     *  Constructeur
     *
     *  \param title Titre
     *  \param min Borne minimum
     *  \param max Borne maximum
     */
    XPositionBar(const QString& title, double min, double max);

    /*!
     *  Retourne la valeur
     *
     *  \return Valeur (coordonnée x)
     */
    double getValue() const;

    /*!
     *  Définit la valeur.
     *
     *  \param value Valeur (coordonnée x)
     */
    void setValue(double value);

    /*!
     *  Définit les bornes.
     *
     *  \param min Borne minimum
     *  \param max Borne maximum
     */
    void setRange(double min, double max);

    /*!
     *  Indique si le contrôle est coché.
     *
     *  \return Vrai s'il est coché, sinon faux
     */
    bool isChecked() const;

    /*!
     *  Définit si le contrôle est coché.
     *
     *  \param checked Coché
     */
    void setChecked(bool checked);

    /*!
     *  Réinitialise le contrôle.
     */
    void reset();



    public slots:

    /*!
     *  Réceptionne le signal du bouton "acceptButton".
     *
     *  \param accepted Valeur d'acceptation
     */
    void acceptChanged(bool accepted);

    /*!
     *  Réceptionne le signal de la barre de défilement "scrollBar".
     *
     *  \param value Valeur à convertir
     */
    void valueChanged(int value);

    /*!
     *  Réceptionne le signal du modificateur "spinBox".
     *
     *  \param value Coordonnée x
     */
    void valueChanged(double value);



    protected:

    /*!
     *  Evénement clavier.
     *
     *  \param event Evénement
     */
    void keyPressEvent(QKeyEvent* event);



    signals:

    /*!
     *  Signal émis lorsque la position est changée.
     *
     *  \param value Coordonnée x
     */
    void xPositionChanged(double value);

    /*!
     *  Signal émis lorsque la position est acceptée.
     *
     *  \param value Coordonnée x
     */
    void xPositionAccepted(double value);

    /*!
     *  Signal émis lorsque la position est annulée.
     */
    void xPositionAborted();
};

#endif // X_POSITION_BAR_H
