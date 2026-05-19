#ifndef BASEPARSER_H
#define BASEPARSER_H

#include "bigfraction.h"

class BaseParser {
public:
    BaseParser();

    BigInteger WholeToTenth(std::string digit, int p);
    BigFraction RationalToTenth(std::string digit, int p);

    BigFraction FromPToTenth(std::string digit, int p);

private:
};

#endif // BASEPARSER_H
