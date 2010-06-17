#include "Scanner.h"

// Creation du scanner
Scanner::Scanner(std::string input) : input(input)
{
    this->nbLeftParen = 0;
    this->nbRightParen = 0;

    tokenNames.push_back("END_OF_LINE");
    tokenNames.push_back("NAMED_FONCTION");
    tokenNames.push_back("POLYNOMIAL");
    tokenNames.push_back("LEFT_PAREN");
    tokenNames.push_back("RIGHT_PAREN");
    tokenNames.push_back("PLUS");
    tokenNames.push_back("MINUS");
    tokenNames.push_back("TIMES");
    tokenNames.push_back("DIV");
    tokenNames.push_back("POW");
    tokenNames.push_back("UNKNOWN");

    currentToken = UNKNOWN;

    currentTokenPosition = 0;

    nextChar();

}

// Changer la chaine d'entree
void Scanner::setInput(std::string input)
{
    this->input = input;
    this->clean();
}

// Prochain token
void Scanner::nextToken()
{

    buffer.clear();
    identifier.clear();

    // Passer les espaces
    if (currentChar == ' ')
        nextChar();

    switch(currentChar)
    {

        // Operateurs
        case '-' :
        {
            nextChar();
            currentToken = MINUS;
            break;
        }
        case '+' :
        {
            nextChar();
            currentToken = PLUS;
            break;
        }
        case '*' :
        {
            nextChar();
            currentToken = TIMES;
            break;
        }
        case '/' :
        {
            nextChar();
            currentToken = DIV;
            break;
        }
        case '^' :
        {
            nextChar();
            currentToken = POW;
            break;
        }

        // Polynome
        case VARIABLE :
        case '0' :
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
        {
            currentToken = POLYNOMIAL;

            while(isdigit(currentChar))
            {
                    buffer += currentChar;
                    next();
            }

            // Partie decimale
            if(currentChar == '.')
            {
                buffer += currentChar;
                next();

                // Erreur
                if (!isdigit(currentChar))
                {
                    // Sauver la position de l'erreur
                    int position = currentTokenPosition;

                    clean();
                    throw new ParserError(DIGIT_EXPECTED[language], position - 1);
                }

                while(isdigit(currentChar))
                {
                    buffer += currentChar;
                    next();
                }

            }

            // Variable
            if (isVariable(currentChar))
            {
                buffer += currentChar;
                next();

                // Exposant
                if(currentChar == '^')
                {
                    next();

                    // Exposant entier
                    if (isdigit(currentChar))
                    {
                        while(isdigit(currentChar))
                        {
                            buffer += currentChar;
                            next();
                        }
                    }

                    // Le polynome est termine, ce qui suit est une expression
                    else
                    {
                        currentChar = '^';
                        currentTokenPosition -= 1;
                    }

                }
            }

            identifier = buffer;
            break;

        }
        case '(' :
        {
            this->nbLeftParen++;
            nextChar();
            currentToken = LEFT_PAREN;
            break;
        }
        case ')' :
        {
            this->nbRightParen++;
            nextChar();
            currentToken = RIGHT_PAREN;
            break;
        }

        // Fin de ligne
        case '\n' :
        {
            currentToken = END_OF_LINE;
            break;
        }

        // Autres caracteres
        default :
        {

            // Caractere inconnu
            if (!isalpha(currentChar))
            {
                currentToken = UNKNOWN;

                // Sauver la position de l'erreur
                int position = currentTokenPosition;
                clean();

                throw new ParserError(UNKNOWN_CHAR[language], position);
            }

            // Constantes pi
            if(tolower(currentChar) == 'p')
            {
                buffer += currentChar;
                next();
                if(tolower(currentChar) == 'i')
                {
                    currentToken = POLYNOMIAL;
                    buffer += currentChar;
                    nextChar();
                }
            }

            // Constantes pi
            if(tolower(currentChar) == 'e')
            {
                buffer += currentChar;
                next();
                currentToken = POLYNOMIAL;
            }

            // Fonction nommee (sin, log, etc.)
            while(isalpha(currentChar))
            {
                currentToken = NAMED_FONCTION;
                buffer += currentChar;
                nextChar();
            }
            identifier = buffer;
            break;
        }

    }
}

// Nom du token
std::string Scanner::currentTokenName() const
{
    return tokenNames.at(currentToken);
}

// Representation complete du token
std::string Scanner::representation() const
{
    // Token parametre
    if(currentToken == NAMED_FONCTION || currentToken == POLYNOMIAL)
        return currentTokenName() + '(' + identifier + ')';

    else
        return currentTokenName();
}

// Indique si le scanner a termine
bool Scanner::hasFinished() const
{
    return currentToken == END_OF_LINE;
}

// Sauter les espaces
void Scanner::nextChar()
{
    // Avancer tant qu'il y a des espaces
    do
    {
        next();
    }
    while(currentChar == ' ');
}

// Prochain caractere direct
void Scanner::next()
{
    if (currentTokenPosition < (int)input.size())
    {
        currentChar = input.at(currentTokenPosition);
        currentTokenPosition++;
    }
    else
        currentChar = '\n';
}

// Reinitialiser le scanner
void Scanner::clean()
{
    this->nbLeftParen = 0;
    this->nbRightParen = 0;

    currentToken = UNKNOWN;
    currentTokenPosition = 0;
    nextChar();

    // Effacer les buffer
    buffer.clear();
    identifier.clear();

}

// Retourne l'identifiant
std::string Scanner::getIdentifier()
{
    return this->identifier;
}

// Indique si la caractere courant est une variable
bool Scanner::isVariable(char currentChar)
{
    return tolower(currentChar) == INDETERMINATE;
}

// Indique l'egalite au niveau des parantheses
int Scanner::egalityParen()
{
    if (nbLeftParen < nbRightParen)
        return -1;
    else if(nbLeftParen > nbRightParen)
        return 1;
    else
        return 0;
}
