#ifndef DIGITTOKENIZER_H
#define DIGITTOKENIZER_H

#include <string>

class DigitTokenizer
{
public:
    DigitTokenizer();
    std::string CharToDigit(std::string input);
private:
    std::string memory;
    long long memory_start;
};

#endif // DIGITTOKENIZER_H
