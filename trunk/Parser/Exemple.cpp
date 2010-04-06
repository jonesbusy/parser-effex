#include <iostream>
#include <cstdlib>

#include <cmath>
#include <iomanip>

#include "Parser.h"

using namespace std;

int main()
{
    // Fabrication de polynomes

    Parser parser("");

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
            for (double i = -1 ; i < 1 ; i += 0.0625)
                cout << expression->eval(i) << endl;


    }
	
    return EXIT_SUCCESS;
}
