#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

/*!
 *  \mainpage Librairie Expression
 *  \section Description
 *
 *  Cette librairie fournie un structure afin de representer
 *  une expression quelconque.
 *
 *  \subsection Structure
 *  La structure de donnee utilisee est un simple arbre binaire contant les
 *  differents noeud tel que Operation, Polynomial et NamedFunction.
 *
 *  La racine quand e elle se nomme IExpression et est une interface permettant
 *  d'appliquer l'operation d'evaluation sur l'entier de l'arbre. Par le biais
 *  du polymorphisme et de la liaison dynamique, les differentes evaluations vont
 *  etre effectuees sur les fonctions nommees ou les polynomes.
 *  Lors de l'arrivee sur un noeud Operation le sous-arbre gauche et le sous-arbre
 *  droit sont evalues puis le resultat est applique a l'operateur (+, -, *, /)
 *  ou a la fonction (sin, cos, abs, etc...)
 */


/*!
 *  \file IExpression.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 03.03.2010
 *
 *  Permet de representer et fournir une interface pour
 *  evaluer differentes expressions mathematiques ou
 *  simples expressions.
 */



#include "ExpressionExport.h"
#include "Cases.h"

/*! \class IExpression
 *
 * Interface pour representer une expression quelconque.
 */
class DLL_EXPORT IExpression
{
    public :

    /*!
     *  Fonction virtuelle pure. Permet d'evaluer l'expression
     *  a une certaine valeur.
     *  Doit etre redefinie pour toute les fonctions.
     *
     *  \param value Valeur a evaluer
     *  \param cases Case pour la detection des discontinuites.
     *  (Cases.h)
     *  \return La valeur d'evaluation (y = ...)
     */
	virtual double eval(double value, Cases* cases = NULL) const = 0;

};


#endif // EXPRESSION_H_INCLUDED
