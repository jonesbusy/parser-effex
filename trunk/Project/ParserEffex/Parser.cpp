#include "Parser.h"

Parser::Parser(std::string input)
{
    // Creation du scanner
    this->scanner = new Scanner(input);

    // Creation des deux fabriques
    this->factoryNamedFunction = new FactoryNamedFunction();
    this->factoryPolynomial = new FactoryPolynomial();
}

Parser::~Parser()
{
    delete scanner;
    delete factoryNamedFunction;
    delete factoryPolynomial;
}


void Parser::setInput(std::string input)
{
    this->scanner->setInput(input);
    this->scanner->clean();
}

IExpression* Parser::parse()
{
    // Remise a zero du scanner
    scanner->clean();

    // Pour recuperer notre arbre d'expression
    IExpression* e;

    // Creation de l'expression
    try
    {
        scanner->nextToken();
        e = expression();
    }

    // Ne pas propager d'erreur a l'exterieur
    catch (ParserError* e)
    {
        this->error = e;
        return NULL;
    }

    // Trop de paranthese droite
    if(scanner->egalityParen() == -1)
    {
        this->error = new ParserError(TOO_MANY_RIGHT_PARENT[language], scanner->currentTokenPosition);
        return NULL;
    }

        // Retourner le nouvel arbre syntaxique
    return e;

}

ParserError* Parser::getError() const
{
    return this->error;
}

IExpression* Parser::expression() const
{
    // Sauver la position courante
    int position = scanner->currentTokenPosition;

    IExpression* result = term();

    // Non valide apres un terme
    if(!isOperator(scanner->currentToken) && scanner->currentToken != RIGHT_PAREN && scanner->currentToken != END_OF_LINE)
       throw new ParserError(OPERATOR_EXPECTED[language], position);

    // Recuperer les termes
    while(scanner->currentToken == PLUS || scanner->currentToken == MINUS)
    {
        // Operateur
        Tokens op = scanner->currentToken;
        scanner->nextToken();

        // Effectuer l'operation correspondante
        if(op == PLUS)
            result = new Operation('+', result, term());
        else
            result = new Operation('-', result, term());

    }

    return result;
}

IExpression* Parser::term() const
{
    // Gauche
    IExpression* tree = unary();

    // Recuperer les facteurs
    while(scanner->currentToken == TIMES || scanner->currentToken == DIV)
    {
        // Operateur
        Tokens op = scanner->currentToken;
        scanner->nextToken();

        // Sous arbre correspondant
        if(op == TIMES)
            tree = new Operation('*', tree, unary());
        else
            tree = new Operation('/', tree, unary());

    }

    return tree;
}

IExpression* Parser::unary() const
{

    // Sauver la position courante
    int position = scanner->currentTokenPosition;

    // Sous arbre
    IExpression* tree;

    // Moin unaire
    if(scanner->currentToken == MINUS)
    {
        scanner->nextToken();

        // Facteur de droite
        IExpression* nextFactor = factor();
        if (nextFactor == NULL)
            throw new ParserError(MISSING_OPERAND[language], position);

        // Changer le signe du prochain facteur
        tree = new Operation('*', new Polynomial(-1), nextFactor);

    }

    // Plus unaire
    else if (scanner->currentToken == PLUS)
    {
        scanner->nextToken();
        tree = factor();
    }

    else
        tree = factor();

    // Deuxieme facteur inexistant
    if(tree == NULL)
        throw new ParserError(MISSING_OPERAND[language], position);

    return tree;

}

IExpression* Parser::factor() const
{

    // Sauver la position courante
    int position = scanner->currentTokenPosition;

    // Sous-arbre
    IExpression* tree = exponent();

    while(scanner->currentToken == POW)
    {
        scanner->nextToken();

        // Prochain exposant
        IExpression* nextExponent = exponent();
        if (nextExponent == NULL)
            throw new ParserError(MISSING_OPERAND[language], position);

        // Construire le nouvel arbre
        tree = new Operation('^', tree, nextExponent);

    }

    return tree;
}

IExpression* Parser::exponent() const
{

    // Sauver la position courante
    int position = scanner->currentTokenPosition;

    // Au depart l'arbre est null
    IExpression* tree = NULL;

    // Polynome
    if(scanner->currentToken == POLYNOMIAL)
    {
        // Recuperer l'instance de fonction
        AbstractFunction* function = factoryPolynomial->getInstance(scanner->getIdentifier());

        // Ne devrait jamais arriver, car le scanner s'assure de passer
        // un polynome correcte a la fabrique
        if (function == NULL)
            throw new ParserError("Cannot parse polynomial", position);

        // Feuille de l'arbre
        else
            tree = function;

        scanner->nextToken();

    }

    // Fonction nommee
    else if(scanner->currentToken == NAMED_FONCTION)
    {

        // Pour recuperer le nom de la fonction
        std::string name = scanner->getIdentifier();

        // Recuperer l'instance
        AbstractFunction* function = factoryNamedFunction->getInstance(name);

        // Impossible de fabriquer la fonction
        if (function == NULL)
            throw new ParserError(UNKNOWN_FUNCTION[language], position - name.size());

        // On doit trouver une paranthese ouvrante
        scanner->nextToken();
        if (scanner->currentToken == LEFT_PAREN)
        {
            scanner->nextToken();

            // Nouvelle operation fonction function(expression())
            // Feuille de l'arbre
            tree = new Operation('f', function, expression(), name);

            // Doit se terminer par une paranthese
            if(scanner->currentToken == RIGHT_PAREN)
                scanner->nextToken();
            else
                throw new ParserError(RIGHT_PAREN_EXPECTED[language], position);

        }

        // Autre chose apres le nom de la fonction
        else
            throw new ParserError(LEFT_PAREN_EXPECTED[language], position);


    }

    // Paranthese gauche
    else if(scanner->currentToken == LEFT_PAREN)
    {

        scanner->nextToken();

        // Expression complete dans la paranthese
        tree = expression();

        // Doit se terminer avec une paranthese droite
        if(scanner->currentToken == RIGHT_PAREN)
            scanner->nextToken();
        else
            throw new ParserError(RIGHT_PAREN_EXPECTED[language], position);

    }

    // Un operateur sans operande
    else
    {
        if (scanner->currentToken != END_OF_LINE)
            throw new ParserError(MISSING_OPERAND[language], position);
    }

    return tree;
}

bool Parser::isOperator(Tokens token) const
{
    return token == MINUS || token == PLUS || token == TIMES || token == DIV || token == POW;
}
