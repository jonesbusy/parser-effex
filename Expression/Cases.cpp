#include "Cases.h"

void Cases::clear()
{
    cases.clear();
}

void Cases::add(int value)
{
    cases.push_back(value);
}

bool Cases::equals(const Cases& c) const
{
    if (c.cases.size() != cases.size())
        return false;

    for (unsigned int i = 0; i < cases.size(); i++)
        if (c.cases[i] != cases[i])
            return false;

    return true;

}

bool operator == (const Cases& c1, const Cases& c2)
{
    return c1.equals(c2);
}
