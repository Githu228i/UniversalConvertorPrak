#include "baseformatter.h"

#include <QMessageBox>

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
    std::unordered_map<std::string, size_t> positions;
    positions.reserve(200000);
    result.reserve(300000);
    if (rational != 0) {
        result += '.';
        size_t i = 0;
        std::string num;
        std::string key = rational.num().ToString() + "/" + rational.den().ToString();
        key.reserve(200000);
        while (rational != 0 && i < 100001 && positions.find(key) == positions.end()) {
            if (i % 1000 == 0) qDebug() << i / 1000 << ' ';
            positions.emplace(key, result.size());
            rational *= q;
            num = std::to_string(rational.GetWholePart()[0]);
            if (std::stoi(num) < 10) result += num;
            else if (std::stoi(num) <= 35) result += ('A' + std::stoi(num) - 10);
            else result += "[" + num + "]";
            rational = rational.GetRemainder();
            i+=1;
            key.clear();
            key += rational.num().ToString();
            key += "/";
            key += rational.den().ToString();
        }
        if (i == 100001) QMessageBox::critical(nullptr, "Ошибка", QString::fromStdString("The output is too long! Only the first 100,000 characters were displayed."));
        else {
            if (positions.find(key) != positions.end()) {
                result.insert(positions[key], 1, '(');
                result += ')';
            }
        }
    }
    qDebug() << "formatter";
    return result;
}
