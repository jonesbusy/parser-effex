#include "ParserError.h"

ParserError::ParserError(std::string message, int position) throw() : message(message), position(position)
{

}

ParserError::~ParserError() throw()
{

}

const char* ParserError::what() const throw()
{
    std::ostringstream out;
    out << position;
    return (message + " at position " + out.str()).c_str();
}

std::string ParserError::getMessage() const
{
    return this->message;
}

int ParserError::getPosition() const
{
    return this->position;
}
