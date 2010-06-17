#include <iostream>
#include <cstdlib>

#include <cmath>
#include <iomanip>

#include "Parser.h"

using namespace std;

int main()
{
    // Le parser
    Parser parser;


    while(true)
    {
        std::string saisie;
        cout << "Entrer une fonction : " ;
        getline(cin, saisie);
        parser.setInput(saisie);

        cout << endl;

        IExpression* expression = parser.parse();

        if(expression == NULL)
            cout << parser.getError()->what() << endl << endl;
        else

            // Compute
            for (double i = -5 ; i <= 5 ; i += 0.1)
                cout << expression->eval(i) << endl;

    }

    return EXIT_SUCCESS;
}
