/*******************************************************************
|
| File         : Cases.h
|
| Description  : Permet d'aider les plotters a dessiner correctement
|                les fonctions discontinues. Lors des differentes
|                operations susceptibles de creer une discontinuite
|                (asympote verticale), le case est rempli des valeurs
|                suivante :
|                (-1 si l'évaluation est négative, 1 si positive et
|                0 si l'evaluation vaut 0)
|
|                Exemple : 1 / (x - 2) pour une évaluation de -3 a 3
|                par pas de 1. Pour le denominateur, le case
|                contiendra [-1, -1, -1, -1, 0, 1].
|
|                Le case est utilise pour les operations suivantes :
|
|                - Division
|                - Tangeante
|                - Valeur absolue
|
|                Par defaut, le case est NULL
|
| Author       : Pascal Berberat
|                Valentin Delaye
|
| Created      : 12.05.2010
|
| Modified     : -
|
| C++ std      : <vector>
|
| Dependencies : -
|
| Version      : 1.0
|
*******************************************************************/

#ifndef CASES_H_INCLUDED
#define CASES_H_INCLUDED

#define BUILD_DLL_E

/*
* Inclure ce fichier pour l'export DLL
*/
#ifdef BUILD_DLL_E
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#include <vector>

class DLL_EXPORT Cases
{

private:


public:

    /***************************************************************
    | Description  : Les differents cases
    ***************************************************************/
    std::vector<int> cases;

    /***************************************************************
    | Description  : Vide le case et toutes les valeurs ajoutes
    |                a l'aide de la methode add(int)
    |
    | Visibility   : Public
    |
    | Parameters   : -
    |
    | Return value : -
    ***************************************************************/
    void clear();

    /***************************************************************
    | Description  : Ajoute un nouveau case dans la liste
    |
    | Visibility   : Public
    |
    | Parameters   : value - La valeur
    |
    | Return value : -
    ***************************************************************/
    void add(int value);

    /***************************************************************
    | Description  : Permet de comparer deux cases
    |
    | Visibility   : Public
    |
    | Parameters   : c1 - Case a comparer avec l'objet courant
    |
    | Return value : True les cases sont egaux, false sinon
    ***************************************************************/
    bool equals(const Cases& c) const;

    /***************************************************************
    | Description  : Permet de comparer deux cases
    |
    | Visibility   : Public
    |
    | Parameters   : c1 - Premier case
    |                c2 - Deuxieme case
    |
    | Return value : True les cases sont egaux, false sinon
    ***************************************************************/
    friend bool operator == (const Cases& c1, const Cases& c2);

};

#endif // CASES_H_INCLUDED
