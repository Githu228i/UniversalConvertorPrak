#include "baseconverter.h"

BaseConverter::BaseConverter() {}

std::string BaseConverter::convert(std::string input, double p, double q) {
    input = tokenizer.CharToDigit(input);
    bool Good = validator.InputCheck(input, p, q);
    if (!Good) throw std::invalid_argument("Error! Invalid input!");
    return (formatter.FromTenthToQ(parser.FromPToTenth(input, p), q));
}
