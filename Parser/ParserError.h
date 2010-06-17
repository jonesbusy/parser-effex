#ifndef PARSERERROR_H_INCLUDED
#define PARSERERROR_H_INCLUDED

/**
 *  \file ParserMessage.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 04.03.2010
 *
 * Permet de representer une erreur du parseur.
 */

#include <string>
#include <sstream>
#include <exception>

#include "ParserMessage.h"

/*! \class ParserError
 *
 *  Permettre de representer une erreur de parsage
 *  l'erreur est representee par un message et une
 *  position d'erreur.
 *
 */
class ParserError : public std::exception
{
    public :

    /*!
     *  Constructeur. Permet de creer une nouvelle erreur.
     *
     *  \param message Le message d'erreur
     *  \param position La position de l'erreur
     */
    ParserError(std::string message, int position) throw();

    /*!
     *  Destructeur.
     */
    virtual ~ParserError() throw();

    /*!
     *  Permet de retourner le message d'erreur complet.
     *  (Position + message)
     *
     *  \return Message d'erreur
     */
    virtual const char* what() const throw();

    /*!
     *  Permet de retourner le message d'erreur uniquement.
     *
     *  \return Message d'erreur
     */
    std::string getMessage() const;

    /*!
     *  Permet de retourner la position de l'erreur.
     *
     *  \return La position de l'erreur
     */
    int getPosition() const;



    private :

    /*! Le message d'erreur */
    std::string message;

    /*! Position de l'erreur */
    int position;

};

#endif // PARSERERROR_H_INCLUDED
