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
 *  La classe CalcButton est un contr�le personnalis� qui permet d'associer un
 *  "tag" � un bouton.
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
     *  D�finit le tag.
     *
     *  \param tag Tag
     */
    void setTag(const QString& tag);



    public slots:

    /*!
     *  R�ceptionne le signal du bouton et envoie le tag.
     */
    void sendClickedTag();



    signals:

    /*!
     *  Signal �mis lorsque le bouton est cliqu�.
     *
     *  \param tag Tag
     */
    void clicked(QString tag);
};

#endif // CALC_BUTTON_H
