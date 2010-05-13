#include "Operation.h"

Operation::Operation(char operation, IExpression* left, IExpression* right, std::string name) : operation(operation), left(left), right(right), name(name)
{

}


Operation::~Operation()
{
    delete right;
    delete left;
}

double Operation::eval(double value, Cases* cases) const
{
    switch(operation)
    {
        // Effectuer l'operation
        case '+' :  return left->eval(value, cases) + right->eval(value, cases);
        case '-' : return left->eval(value, cases) - right->eval(value, cases);
        case '*' :  return left->eval(value, cases) * right->eval(value, cases);

        // Division
        case '/' :
        {
            double denominator = right->eval(value, cases);

            // Ajouter le bon case
            if(cases != NULL)
            {
                if(denominator < 0)
                    cases->add(-1);
                else if(denominator > 0)
                    cases->add(1);
                else
                    cases->add(0);
            }

            return left->eval(value, cases) / denominator;
        }

        case '^' :  return pow(left->eval(value, cases), right->eval(value, cases));

        // Unaire (fonction)
        case 'f' :
        {

            // Evaluer ce qu'il y a l'interieur de la fonction
            double content = right->eval(value, cases);

            // On doit remplir le case
            if (cases != NULL && this->name != "")
            {
                // Tengante
                if(this->name == "tan")
                    cases->add((int)floor((content-PI/2.0)/PI));

                // Valeur absolue
                else if(this->name == "abs")
                {
                    if(content < 0)
                        cases->add(-1);
                    else if(content > 0)
                        cases->add(1);
                    else
                        cases->add(0);
                }
            }

            // Appliquer ensuite la fonction
            return left->eval(content, cases);

        }

        default  : return 0.0;
    }
}
