#include "baseparser.h"

BaseParser::BaseParser() {}

BigInteger BaseParser::WholeToTenth(std::string digit, int p) {
    BigInteger temp;
    BigInteger Pow = 1;
    int CurNum = 0;
    int num;
    int numSize = 1;
    char part;
    for (int i = digit.size() - 1; i >= 0; --i) {
        part = digit[i];
        if (part == '['){
            temp += (Pow * BigInteger(CurNum));
            Pow *= p;
            CurNum = 0;
            numSize = 1;
        } else if (part == ']') {
            CurNum = 0;
            numSize = 1;
        } else {
            num = part - '0';
            CurNum = CurNum + num * numSize;
            numSize *= 10;
        }
    }
    return temp;
}

BigFraction BaseParser::RationalToTenth(std::string digit, int p) {
    BigFraction temp(0, 1);
    BigInteger Pow = p;
    char part;
    int CurNum = 0;
    int num;
    for (int i = 0; i < digit.size(); ++i) {
        part = digit[i];
        if (part == ']'){
            temp += BigFraction(CurNum, Pow);
            Pow *= p;
            CurNum = 0;
        } else if (part == '[') {
            CurNum = 0;
        } else {
            num = part - '0';
            CurNum = CurNum * 10 + num;
        }
    }
    return temp;
}

BigFraction BaseParser::FromPToTenth(std::string digit, int p) {
    bool IsWhole = true;
    bool IsRational = false;
    bool IsPeriod = false;
    BigInteger whole = 0;
    BigFraction rational(0, 1);
    BigInteger PowPRat(1);
    BigFraction period(0, 1);
    BigInteger PowPSize(1);
    BigInteger PeriodTenth;
    std::string wholeStr = "";
    std::string rationalStr = "";
    std::string periodStr = "";
    char part;
    for (int i = 0; i < digit.size(); ++i) {
        part = digit[i];
        if (part == '.') {
            IsRational = true;
            IsWhole = false;
        } else if (part == '(') {
            IsPeriod = true;
            IsWhole = false;
            IsRational = false;
        } else if (part == ')') {
            continue;
        } else if (IsWhole) {
            wholeStr += part;
        } else if (IsRational) {
            rationalStr += part;
        } else if (IsPeriod) {
            periodStr += part;
        }
    }
    whole = WholeToTenth(wholeStr, p);
    if (periodStr.size() != 0) {
        PeriodTenth = WholeToTenth(periodStr, p);
        for (int k = 0; k < periodStr.size(); ++k) {
            if (periodStr[k] == ']') PowPSize *= p;
        }
        PowPSize -= 1;
        period = BigFraction(PeriodTenth, PowPSize);
    }
    if (rationalStr.size() != 0) {
        for (int k = 0; k < rationalStr.size(); ++k) {
            if (rationalStr[k] == ']') PowPRat *= p;
        }
        period *= BigFraction(1, PowPRat);
        rational = RationalToTenth(rationalStr, p);
    }
    qDebug() << "parser ";
    return whole + rational + period;
}
