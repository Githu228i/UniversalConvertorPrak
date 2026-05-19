#include "biginteger.h"

#include <exception>
#include <iomanip>
#include <QDebug>

BigInteger::BigInteger() {
    value.push_back(0);
}

BigInteger::BigInteger(long long val) {
    if (val == 0) {
        value.push_back(0);
        return;
    }
    while (val != 0) {
        value.push_back(val % BASE);
        val /= BASE;
    }

}

BigInteger::BigInteger(QString val) {
    for (int i = val.size(); i > 0; i -= BASE_POW) {
        int start = std::max(0, i - BASE_POW);
        int len = i - start;
        int chunk = val.mid(start, len).toInt();
        value.push_back(chunk);
    }
    if (value.empty()) {
        value.push_back(0);
    }
    while (value.size() > 1 && value.back() == 0) {
        value.pop_back();
    }
}

std::string BigInteger::ToString() const{
    std::string res = "";
    for (int i = value.size() - 1; i >= 0; --i) {
        std::string part = std::to_string(value[i]);
        if (i != value.size() -1 && part.size() < BigInteger::BASE_POW) {
            for (int j = 0; j < BigInteger::BASE_POW - part.size(); ++j) {
                res += '0';
            }
        }
        res += part;
    }
    return res;
}

bool BigInteger::IsZero() const {
    if (value.size() == 1 && value[0] == 0) return true;
    return false;
}

BigInteger BigInteger::RightShift(int val) const {
    if (value.size() <= val) return BigInteger(0);
    BigInteger res;
    res.value.clear();
    for (int i = val; i < value.size(); ++i) {
        res.value.push_back(value[i]);
    }
    return res;
}

BigInteger BigInteger::LeftShift(int val) const {
    if (this -> IsZero()) return *this;
    BigInteger res = *this;
    res.value.insert(res.value.begin(), val, 0);
    return res;
}

void BigInteger::Normalization() {
    if (value.size() == 0) {
        value.push_back(0);
        return;
    }
    while (value.size() != 1 && value.back() == 0) {
        value.pop_back();
    }
    return;
}

BigInteger BigInteger::GetBegin(int val) const {
    if (val >= value.size()) return *this;
    BigInteger res;
    res.value.clear();
    for (int i = 0; i < val; ++i) {
        res.value.push_back(value[i]);
    }
    res.Normalization();
    return res;
}

size_t BigInteger::GetSize() {
    return value.size();
}

int BigInteger::BasePow() {
    return BASE_POW;
}

int& BigInteger::operator[](size_t val) {
    if (val >= value.size()) {
        throw std::out_of_range("BigInteger index out of range");
    }
    return value[val];
}

const int& BigInteger::operator[](size_t val) const {
    if (val >= value.size()) {
        throw std::out_of_range("BigInteger index out of range");
    }
    return value[val];
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    BigInteger res;
    int trans = 0;
    for (int i = 0; i < std::max(value.size(), other.value.size()); ++i) {
        if (i != 0) res.value.push_back(0);
        if (i < value.size()) res.value[i] += value[i];
        if (i < other.value.size()) res.value[i] += other.value[i];
        res.value[i] += trans;
        trans = res.value[i] / BASE;
        res.value[i] %= BASE;
    }
    if (trans == 1) {
        res.value.push_back(1);
    }
    return res;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    BigInteger res;
    int trans = 0;
    if (other > *this) {
        throw std::invalid_argument("Error! 2nd operand bigger than 1st one!");
    }
    for(int i = 0; i < value.size(); ++i) {
        if (i != 0) res.value.push_back(0);
        res.value[i] = value[i];
        if (i < other.value.size()) res.value[i] -= other.value[i];
        res.value[i] -= trans;
        trans = 0;
        if (res.value[i] < 0) {
            trans = 1;
            res.value[i] += BASE;
        }
    }
    while (res.value.size() > 1 && res.value.back() == 0) {
        res.value.pop_back();
    }
    return res;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}

BigInteger BigInteger::operator*(const int & other) const {
    long long trans = 0;
    BigInteger res;
    long long temp = 0;
    for (int i = 0; i < value.size(); ++i) {
        if (i != 0) res.value.push_back(0);
        temp = 1LL * value[i] * other;
        temp += trans;
        trans = temp / BASE;
        res.value[i] = temp % BASE;
    }
    if(trans != 0) {
        res.value.push_back(trans);
    }
    return res;
}

BigInteger& BigInteger::operator*=(const int& other){
    *this = *this * other;
    return *this;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger res;
    res.value.clear();
    res.value.assign(value.size() + other.value.size(), 0);
    long long temp = 0;
    long long trans = 0;
    for (int i = 0; i < value.size(); ++i) {
        for (int j = 0; j < other.value.size(); ++j) {
            temp = 1LL * value[i] * other.value[j];
            temp += res.value[i + j];
            res.value[i + j + 1] += temp / BASE;
            res.value[i + j] = temp % BASE;
        }
    }
    res.Normalization();
    return res;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}

BigInteger Karacuba(const BigInteger& lhs, const BigInteger& rhs) {
    if (std::max(lhs.value.size(), rhs.value.size()) <= BigInteger::KARACUBA_MAX) {
        return lhs * rhs;
    }

    BigInteger lhs_copy = lhs;
    BigInteger rhs_copy = rhs;

    while (lhs_copy.value.size() < rhs_copy.value.size()) lhs_copy.value.push_back(0);
    while (rhs_copy.value.size() < lhs_copy.value.size()) rhs_copy.value.push_back(0);

    size_t k = lhs_copy.value.size() / 2;
    BigInteger lhs_low = lhs_copy.GetBegin(k);
    BigInteger lhs_high = lhs_copy.RightShift(k);
    BigInteger rhs_low = rhs_copy.GetBegin(k);
    BigInteger rhs_high = rhs_copy.RightShift(k);
    BigInteger first = Karacuba(lhs_high, rhs_high);
    BigInteger second = Karacuba((lhs_low + lhs_high), (rhs_low + rhs_high));
    BigInteger third = Karacuba(lhs_low, rhs_low);
    second = second - first - third;
    BigInteger res = first.LeftShift(2 * k) + second.LeftShift(k) + third;
    res.Normalization();
    return res;
}

BigInteger BigInteger::operator/(const int& other) const {
    if (other == 0) throw std::invalid_argument("Error! Devision by zero");
    BigInteger res;
    long long trans = 0;
    res.value.assign(value.size(), 0);
    for (int i = value.size() - 1; i >= 0; --i) {
        res.value[i] = (value[i] + trans * BASE) / other;
        trans = (value[i] + trans * BASE) % other;
    }
    res.Normalization();
    return res;
}

BigInteger& BigInteger::operator/=(const int& other) {
    *this = *this / other;
    return *this;
}

int BigInteger::operator%(const int& other) const {
    if (other == 0) throw std::invalid_argument("Error! Devision by zero");
    long long trans = 0;
    for (int i = value.size() - 1; i >= 0; --i) {
        trans = (value[i] + trans * BASE) % other;
    }
    return trans;
}

int& BigInteger::operator%=(const int& other) {
    *this = *this % other;
    return value[0];
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
    if (other.IsZero()) throw std::invalid_argument("Error! Devision by zero!");
    if (other > *this) return BigInteger(0);
    BigInteger res;
    res.value.clear();
    BigInteger trans;
    for (int i = value.size() - 1; i >= 0; --i) {
        trans = (trans.LeftShift(1)) + BigInteger(value[i]);
        if (trans < other) {
            res = res.LeftShift(1);
            continue;
        }
        int Left = 0;
        int Right = BASE - 1;
        while (Left <= Right) {
            int Mid = (Left + Right) / 2;
            if (other * Mid <= trans) {
                Left = Mid + 1;
            } else {
                Right = Mid - 1;
            }
        }
        res = (res.LeftShift(1) + Right);
        trans = trans - other * Right;
    }
    res.Normalization();
    return res;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
    if (other.IsZero()) throw std::invalid_argument("Error! Devision by Zero!");
    if (other > *this) return *this;
    BigInteger trans;
    for (int i = value.size() - 1; i >= 0; --i) {
        trans = trans.LeftShift(1) + BigInteger(value[i]);
        if (trans < other) {
            continue;
        }
        int Left = 0;
        int Right = BASE - 1;
        while (Left <= Right) {
            int Mid = (Left + Right) / 2;
            if (other * Mid <= trans) {
                Left = Mid + 1;
            } else {
                Right = Mid - 1;
            }
        }
        trans = trans - other * Right;
    }
    return trans;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

BigInteger gcd(const BigInteger& lhs, const BigInteger& rhs) {
    if (rhs == 0) return lhs;
    return gcd(rhs, lhs % rhs);
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.value.size() > rhs.value.size()) return true;
    if (lhs.value.size() < rhs.value.size()) return false;
    for (int i = static_cast<int>(lhs.value.size()) - 1; i >= 0; i--) {
        if (lhs.value[i] > rhs.value[i]) return true;
        if (lhs.value[i] < rhs.value[i]) return false;
    }
    return false;
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
    return (!(rhs > lhs));
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
    return (rhs > lhs);
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
    return (!(lhs > rhs));
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
    return lhs.value == rhs.value;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
    return (!(lhs == rhs));
}

std::ostream& operator<<(std::ostream& out, const BigInteger& val) {
    out << val.ToString();
    return out;
}

QDebug operator<<(QDebug out, const BigInteger& val) {
    out.nospace().noquote();
    out << QString::fromStdString(val.ToString());
    return out;
}

