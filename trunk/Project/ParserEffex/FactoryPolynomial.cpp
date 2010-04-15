#include "FactoryPolynomial.h"

FactoryPolynomial::FactoryPolynomial()
{
    constants["pi"] = 3.14159265;
    constants["e"] = 2.71828183;
}

FactoryPolynomial::~FactoryPolynomial()
{
    constants.clear();
}

Polynomial* FactoryPolynomial::getInstance(std::string input) const
{

    // Diminuer la casse
    std::transform(input.begin(), input.end(), input.begin(), tolower);

    // Pour parcourir la chaine
    size_t indice = 0;

    // Pour creer le coeeficiant et l'exposant
    double coefficiant;
    int exponent;

    // Buffer pour parser notre chaine
    std::string buffer;

    // Chercher si une constante existe sous ce nom
    std::map<std::string, double>::const_iterator search = constants.find(input);


    // Constante
    if (search != constants.end())
        return new Polynomial(search->second);


    // Doit commencer par 0-9 ou x
    else if(isDigitAt(input, indice) || isCharAt(input, indice, VARIABLE))
    {
        // Recuperer la partie entiere du coefficiant
        while(isDigitAt(input, indice))
        {
                buffer += input.at(indice);
                indice++;
        }

        // Partie decimale
        if(isCharAt(input, indice, '.'))
        {
            buffer += input.at(indice);
            indice++;

            // On attends un digit apres le point
            if (!isDigitAt(input, indice))
                return NULL;

            // Recuperer les decimales
            while(isDigitAt(input, indice))
            {
                buffer += input.at(indice);
                indice++;
            }

        }

        // Si le coefficiant n'existe pas (ex : x^2) il vaut 1
        if(buffer.empty())
            coefficiant = 1.0;

        // Sinon recuperer la valeur double
        else
            coefficiant = strtod(buffer.c_str(), NULL);

        buffer.clear();


        // Il faut ensuite la variable
        if (isCharAt(input, indice, VARIABLE))
        {
            indice++;

            // Il peut y avoir un ^
            if(isCharAt(input, indice, '^'))
            {
                indice++;

                // Exposant entier
                if (isDigitAt(input, indice))
                {
                    while(isDigitAt(input, indice))
                    {
                        buffer += input.at(indice);
                        indice++;
                    }
                }

                // Sinon erreur
                else
                    return NULL;

            }

            // Signe ^ non obligatoire, donc que des entiers
            else if (isDigitAt(input, indice))
            {
                while(isDigitAt(input, indice))
                {
                    buffer += input.at(indice);
                    indice++;
                }

            }

            // Si on est pas arrive a la fin de la chaine, il y a un probleme
            if(indice != input.size())
                return NULL;


        if(buffer.empty())
            exponent = 1;
        else
            exponent = atoi(buffer.c_str());

        }

        // Pas de x donc exposant a 0
        else
            exponent = 0;

        // Retourner le polynome
        return new Polynomial(coefficiant, exponent);

    }

    // Si on ne commence pas par un digit ou x, erreur
    else
        return NULL;

}

bool FactoryPolynomial::isCharAt(std::string input, size_t position, char value) const
{
    return position < input.size() && input.at(position) == value;
}

bool FactoryPolynomial::isDigitAt(std::string input, size_t position) const
{
    return position < input.size() && isdigit(input.at(position));
}
