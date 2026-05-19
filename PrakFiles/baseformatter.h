#ifndef BASEFORMATTER_H
#define BASEFORMATTER_H

#include "bigfraction.h"
#include <string>

class BaseFormatter
{
public:
    BaseFormatter();

    std::string FromTenthToQ(BigFraction digit, int q);

private:
};

#endif // BASEFORMATTER_H
