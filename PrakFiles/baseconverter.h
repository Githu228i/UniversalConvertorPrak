#ifndef BASECONVERTER_H
#define BASECONVERTER_H

#include "baseformatter.h"
#include "baseparser.h"
#include "digittokenizer.h"
#include "inputvalidator.h"
#include <string>

class BaseConverter
{
public:
    BaseConverter();

    std::string convert(std::string input, double p, double q);

private:
    BaseFormatter formatter;
    BaseParser parser;
    InputValidator validator;
    DigitTokenizer tokenizer;
};

#endif // BASECONVERTER_H
