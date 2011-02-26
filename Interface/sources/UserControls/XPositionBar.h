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
 *  La classe XPositionBar est un contr�le personnalis� qui permet de choisir
 *  une valeur de x dans un domaine fini.
 */

class XPositionBar : public QFrame
{
    Q_OBJECT

    private:

    /*! Echelle de la barre de d�filement */
    static const int PARTS = 500;

    /*! Disposition globale */
    QHBoxLayout* layout;

    /*! Label */
    QLabel* label;

    /*! Valeur num�rique */
    QDoubleSpinBox* spinBox;

    /*! Barre de d�filement */
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
     *  \return Valeur (coordonn�e x)
     */
    double getValue() const;

    /*!
     *  D�finit la valeur.
     *
     *  \param value Valeur (coordonn�e x)
     */
    void setValue(double value);

    /*!
     *  D�finit les bornes.
     *
     *  \param min Borne minimum
     *  \param max Borne maximum
     */
    void setRange(double min, double max);

    /*!
     *  Indique si le contr�le est coch�.
     *
     *  \return Vrai s'il est coch�, sinon faux
     */
    bool isChecked() const;

    /*!
     *  D�finit si le contr�le est coch�.
     *
     *  \param checked Coch�
     */
    void setChecked(bool checked);

    /*!
     *  R�initialise le contr�le.
     */
    void reset();



    public slots:

    /*!
     *  R�ceptionne le signal du bouton "acceptButton".
     *
     *  \param accepted Valeur d'acceptation
     */
    void acceptChanged(bool accepted);

    /*!
     *  R�ceptionne le signal de la barre de d�filement "scrollBar".
     *
     *  \param value Valeur � convertir
     */
    void valueChanged(int value);

    /*!
     *  R�ceptionne le signal du modificateur "spinBox".
     *
     *  \param value Coordonn�e x
     */
    void valueChanged(double value);



    protected:

    /*!
     *  Ev�nement clavier.
     *
     *  \param event Ev�nement
     */
    void keyPressEvent(QKeyEvent* event);



    signals:

    /*!
     *  Signal �mis lorsque la position est chang�e.
     *
     *  \param value Coordonn�e x
     */
    void xPositionChanged(double value);

    /*!
     *  Signal �mis lorsque la position est accept�e.
     *
     *  \param value Coordonn�e x
     */
    void xPositionAccepted(double value);

    /*!
     *  Signal �mis lorsque la position est annul�e.
     */
    void xPositionAborted();
};

#endif // X_POSITION_BAR_H
