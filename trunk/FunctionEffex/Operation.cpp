#include "Operation.h"

Operation::Operation(char operation, IExpression* left, IExpression* right) : operation(operation), left(left), right(right)
{

}


Operation::~Operation()
{
    delete right;
    delete left;
}

double Operation::eval(double value) const
{
    switch(operation)
    {
        // Effectuer l'operation
        case '+' :  return left->eval(value) + right->eval(value);
        case '-' :  return left->eval(value) - right->eval(value);
        case '*' :  return left->eval(value) * right->eval(value);
        case '/' :  return left->eval(value) / right->eval(value);
        case '^' :  return pow(left->eval(value), right->eval(value));

        // Unaire (fonction)
        case 'f' :  return left->eval(right->eval(value));

        default  : return 0.0;
    }
}
