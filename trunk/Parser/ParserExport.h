#ifndef PARSEREXPORT_H_INCLUDED
#define PARSEREXPORT_H_INCLUDED

/**
 *  \file ParserExport.h
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

#ifdef BUILD_DLL_PARSER
    /*! Pour export DLL */
    #define DLL_EXPORT __declspec(dllexport)
#else
    /*! Pour import DLL */
    #define DLL_EXPORT __declspec(dllimport)
#endif

#endif // PARSEREXPORT_H_INCLUDED
