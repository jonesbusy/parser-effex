#include <iostream>
#include <cstdlib>

#include <cmath>
#include <iomanip>

#include "Parser.h"
#include "Cases.h"

using namespace std;

int main()
{
    // Fabrication de polynomes

    Parser parser;

    Cases* cases = new Cases();

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
                cout << expression->eval(i, cases) << endl;

        cout << endl << "**********************" << endl;
        cout << "Case" << endl;
        for(unsigned int i = 0 ; i < cases->cases.size(); i++)
            cout << cases->cases[i] << endl;

        cases->cases.clear();


    }


    return EXIT_SUCCESS;
}
