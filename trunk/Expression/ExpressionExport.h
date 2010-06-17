#ifndef FUNCTIONEXPORT_H_INCLUDED
#define FUNCTIONEXPORT_H_INCLUDED

/**
 *  \file ExpressionExport.h
 *  \author Valentin Delaye
 *  \version 1.0
 *  \date 19.05.2010
 *
 *  Inclure ce fichier pour les classes ayant besoin d'etre
 *  exportees pour la DLL.
 */

#ifdef DLL_EXPORT
    #undef DLL_EXPORT
#endif

#ifdef BUILD_DLL_EXPRESSION
    /*!
     * Pour export des classes
     */
    #define DLL_EXPORT __declspec(dllexport)
#else
    /*!
     * Pour import des classes
     */
    #define DLL_EXPORT __declspec(dllimport)
#endif

#endif // FUNCTIONEXPORT_H_INCLUDED
