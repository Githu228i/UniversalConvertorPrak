#include "baseformatter.h"

#include <QMessageBox>
#include <map>

BaseFormatter::BaseFormatter() {}

std::string BaseFormatter::FromTenthToQ(BigFraction digit, int q) {
    std::string result = "";
    BigInteger whole = digit.GetWholePart();
    BigFraction rational = digit.GetRemainder();
    while (whole > 0) {
        std::string num = std::to_string(whole % q);
        if (num.size() == 1) result = num + result;
        else if (std::stoi(num) <= 35) {
            char number = 'A' + std::stoi(num) - 10;
            result = number + result;
        } else {
            result = "[" + num + "]" + result;
        }
        whole /= q;
    }
    if (result == "") result += "0";
    size_t wholeSize = result.size();
    std::map<BigFraction, size_t> positions;
    if (rational != 0) {
        result += '.';
        size_t i = 0;
        std::string num;
        while (rational != 0 && i < 100001 && positions.find(rational) == positions.end()) {
            positions.insert({rational, result.size()});
            rational *= q;
            num = std::to_string(rational.GetWholePart()[0]);
            if (std::stoi(num) < 10) result += num;
            else if (std::stoi(num) <= 35) result += ('A' + std::stoi(num) - 10);
            else result += "[" + num + "]";
            rational = rational.GetRemainder();
            ++i;
        }
        if (i == 100001) QMessageBox::critical(nullptr, "Ошибка", QString::fromStdString("The output is too long! Only the first 100,000 characters were displayed."));
        else {
            if (positions.find(rational) != positions.end()) {
                result.insert(positions[rational], 1, '(');
                result += ')';
            }
        }
    }
    return result;
}
