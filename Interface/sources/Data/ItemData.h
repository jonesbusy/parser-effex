#ifndef ITEM_DATA_H
#define ITEM_DATA_H

/*!
 *  \file ItemData.h
 *  \author Pascal Berberat
 *  \date 14.05.2010
 *  \version 1.0
 */

#include <QString>

/*!
 *  \class ItemData
 *
 *  \brief La classe ItemData contient les donn�es li�es � une instance
 *  FunctionItem.
 *
 *  Cette classe permet d'informer les instances de type FunctionItem sur les
 *  donn�es qu'elles sont cens�s repr�senter.
 */

class ItemData
{
    private:

    /*! Nom */
    QString name;

    /*! Domaine de d�finition */
    QString domain;

    /*! Valeur */
    double value;



    public:

    /*!
     *  Constructeur
     *
     *  \param name Nom
     *  \param domain Domaine de d�finition
     *  \param value Valeur
     */
    ItemData(const QString& name, const QString& domain, double value);

    /*!
     *  Retourne le nom.
     *
     *  \return Nom
     */
    const QString& getName() const;

    /*!
     *  Retourne le domaine de d�finition.
     *
     *  \return Domaine de d�finition
     */
    const QString& getDomain() const;

    /*!
     *  Retourne la valeur.
     *
     *  \return Valeur
     */
    double getValue() const;
};

#endif // ITEM_DATA_H
