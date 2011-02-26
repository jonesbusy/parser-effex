#ifndef CALC_BUTTON_H
#define CALC_BUTTON_H

/*!
 *  \file CalcButton.h
 *  \author Pascal Berberat
 *  \date 12.04.2010
 *  \version 1.0
 */

#include <QPushButton>
#include <QString>

/*!
 *  \class CalcButton
 *
 *  La classe CalcButton est un contrôle personnalisé qui permet d'associer un
 *  "tag" à un bouton.
 */

class CalcButton : public QPushButton
{
    Q_OBJECT

    private:

    /*! Tag du bouton */
    QString tag;



    public:

    /*!
     *  Constructeur
     *
     *  \param text Texte
     *  \param tag Tag
     */
    CalcButton(const QString& text, const QString& tag);

    /*!
     *  Retourne le tag.
     *
     *  \return Tag
     */
    QString getTag() const;

    /*!
     *  Définit le tag.
     *
     *  \param tag Tag
     */
    void setTag(const QString& tag);



    public slots:

    /*!
     *  Réceptionne le signal du bouton et envoie le tag.
     */
    void sendClickedTag();



    signals:

    /*!
     *  Signal émis lorsque le bouton est cliqué.
     *
     *  \param tag Tag
     */
    void clicked(QString tag);
};

#endif // CALC_BUTTON_H
