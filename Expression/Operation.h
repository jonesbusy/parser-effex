#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

/**
 * \file Operation.h
 * \author Valentin Delaye
 * \version 2.0
 * \date 17.03.2010
 *
 * Permet d'effectuer une operation sur un noeud de l'arbre.
 */

#include <cmath>
#include <string>

#include "ExpressionExport.h"
#include "IExpression.h"

/*! \class Operation
 *
 * Permet de representer une operation dans l'arbre.
 */
class DLL_EXPORT Operation : public IExpression
{
    private :

    /*! Operation associee */
    char operation;

    /*! Expression a gauche */
    IExpression* left;

    /*! Expression a droite */
    IExpression* right;

     /*! Nom de la fonction si c'est une fonction unaire */
    std::string name;



    public :

    /*!
     *  Constructeur. Permet de creer un nouvelle operation.
     *
     *  \param operation L'operation (+, -, *, etc.)
     *  \param left Expression a gauche
     *  \param right Expression a droite
     *  \param name Le nom de la fonction si
     */
    Operation(char operation, IExpression* left, IExpression* right, std::string name = "");

    /*!
     *  Destructeur.
     */
	virtual ~Operation();

    /*!
     *  Permet d'evaluer l'operation.
     *
     *  \param value Valeur d'evaluation
     *  \param cases Le case pour les discontinuites
     *  \return La valeur d'evaluation (y = ...)
     */
	double eval(double value, Cases* cases = NULL) const;

};

#endif // OPERATION_H_INCLUDED
