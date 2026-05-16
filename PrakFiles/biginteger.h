#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <QVector>
#include <QString>

class BigInteger {
public:
    BigInteger();
    BigInteger(long long val);
    BigInteger(QString val);

    std::string ToString() const;
    bool IsZero() const;

    BigInteger RightShift(int val) const;
    BigInteger LeftShift(int val) const;
    BigInteger GetBegin(int val) const;
    void Normalization();

    BigInteger operator+(const BigInteger& other) const;
    BigInteger& operator+=(const BigInteger& other);
    BigInteger operator-(const BigInteger& other) const;
    BigInteger& operator-=(const BigInteger& other);
    BigInteger operator*(const int& other) const;
    BigInteger& operator*=(const int& other);
    BigInteger operator*(const BigInteger& other) const;
    BigInteger& operator*=(const BigInteger& other);
    friend BigInteger Karacuba(const BigInteger& lhs, const BigInteger& rhs);
    BigInteger operator/(const int& other) const;
    BigInteger& operator/=(const int& other);
    BigInteger operator%(const int& other) const;
    BigInteger& operator%=(const int& other);
    BigInteger operator/(const BigInteger& other) const;
    BigInteger& operator/=(const BigInteger& other);
    BigInteger operator%(const BigInteger& other) const;
    BigInteger& operator%=(const BigInteger& other);

    friend BigInteger gcd(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);


    friend std::ostream& operator<<(std::ostream& out, const BigInteger& val);
    friend QDebug operator<<(QDebug out, const BigInteger& val);
private:
    static const int BASE = 1000000000;
    static const int BASE_POW = 9;
    static const int KARACUBA_MAX = 7;
    std::vector<int> value;
};

#endif // BIGINTEGER_H
