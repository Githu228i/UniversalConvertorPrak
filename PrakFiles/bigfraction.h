#pragma once
#include <iostream>

#include "biginteger.h"

// int gcd1(int first_number, int second_number) {
//     if (second_number == 0) return first_number;
//     return gcd1(second_number, first_number % second_number);
// }

// int gcd(int first_number, int second_number) {
//     return abs(gcd1(first_number, second_number));
// }

class BigFraction {
public:
    BigFraction() : num_(BigInteger(0)), den_(BigInteger(1)) {} // DEFAULT

    BigFraction(BigInteger num, BigInteger den) : num_(num), den_(den) { // CONSTRUCTOR INT INT
        if (den == 0) {
            throw std::invalid_argument("Error! Denominator cant be zero");
        }
        this -> togood();
    }

    explicit BigFraction(BigInteger num) : num_(num), den_(1) {} // CONSTRUCTOR INT

    BigFraction(const BigFraction& other) { // CONSTRUCTOR COPY
        num_ = other.num_;
        den_ = other.den_;
    }

    ~BigFraction() = default; // DESTRUCTOR DEFAULT

    const BigInteger& num() const { return num_; } // GETTER NUM
    const BigInteger& den() const { return den_; } // GETTER DEN

    BigFraction& operator=(const BigFraction& other) { // EQUAL =
        num_ = other.num_;
        den_ = other.den_;
        return *this;
    }

    BigFraction& operator=(const BigInteger& nn) { // EQUAL = int
        num_ = nn;
        den_ = 1;
        return *this;
    }

    // BigFraction operator-() { // MINUS - UNO
    //     BigFraction res = *this;
    //     res.num_ = -1 * num_;
    //     res.den_ = den_;
    //     return res;
    // }

    // BigFraction operator+() { // PLUS + UNO
    //     return *this;
    // }

    friend BigFraction& operator++(BigFraction& frac) { // PLUS PREF ++ UNO
        frac.num_ += frac.den_;
        frac.togood();
        return frac;
    }

    friend BigFraction operator++(BigFraction& frac, int notused) {// PLUS POST ++ UNO
        BigFraction res = frac;
        frac.num_ += frac.den_;
        frac.togood();
        return res;
    }

    friend BigFraction& operator--(BigFraction& frac) { // MINUS PREF -- UNO
        frac.num_ -= frac.den_;
        frac.togood();
        return frac;
    }

    friend BigFraction operator--(BigFraction& frac, int notused) {// MINUS POST -- UNO
        BigFraction res = frac;
        frac.num_ -= frac.den_;
        frac.togood();
        return res;
    }

    friend BigFraction operator+(BigFraction lhs, BigFraction rhs) { // PLUS + BIN
        BigInteger den_lhs = lhs.den_;
        BigInteger den_rhs = rhs.den_;

        BigInteger temp_gcd = gcd (den_lhs, den_rhs);
        den_lhs /= temp_gcd;
        den_rhs /= temp_gcd;

        lhs.num_ = Karacuba(lhs.num_, den_rhs);
        lhs.den_ = Karacuba(lhs.den_, den_rhs);
        rhs.num_ = Karacuba(rhs.num_, den_lhs);

        lhs.num_ += rhs.num_;
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator+(const BigFraction& lhs, const BigInteger& rhs) { // PLUS + BIN frac + int
        return lhs + BigFraction(rhs, 1);
    }

    friend BigFraction operator+(const BigInteger& lhs, const BigFraction& rhs) { // PLUS + BIN int + frac
        return rhs + BigFraction(lhs, 1);
    }

    friend BigFraction operator-(BigFraction lhs, BigFraction rhs) { // MINUS - BIN frac - frac
        BigInteger den_lhs = lhs.den_;
        BigInteger den_rhs = rhs.den_;

        BigInteger temp_gcd = gcd (den_lhs, den_rhs);
        den_lhs /= temp_gcd;
        den_rhs /= temp_gcd;

        lhs.num_ = Karacuba(lhs.num_, den_rhs);
        lhs.den_ = Karacuba(lhs.den_, den_rhs);
        rhs.num_ = Karacuba(rhs.num_, den_lhs);

        lhs.num_ -= rhs.num_;
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator-(const BigFraction& lhs, const BigInteger& rhs) { // MINUS - BIN frac - int
        return lhs - BigFraction(rhs, 1);
    }

    friend BigFraction operator-(const BigInteger& lhs, BigFraction rhs) { // MINUS - BIN int - frac
        return BigFraction(lhs, 1) - rhs;
    }

    friend BigFraction operator*(BigFraction lhs, const BigFraction& rhs) { // MULTIPLICATION *
        lhs.num_ = Karacuba(lhs.num_, rhs.num_);
        lhs.den_ = Karacuba(lhs.den_, rhs.den_);
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator*(BigFraction lhs, const BigInteger& rhs) { // MULTIPLICATION * BIN     frac * int
        lhs.num_ = Karacuba(lhs.num_, rhs);
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator*(const BigInteger& lhs, BigFraction rhs) { // MULTIPLICATION * BIN    int * frac
        rhs.num_ = Karacuba(rhs.num_, lhs);
        rhs.togood();
        return rhs;
    }

    friend BigFraction operator/(const BigFraction& lhs, BigFraction rhs) { // DIVISION / BIN   frac / frac
        if (rhs.num_ == BigInteger(0)) throw std::invalid_argument("Error! Deviding by zero is prohibited!");
        BigInteger den = rhs.den_;
        rhs.den_ = rhs.num_;
        rhs.num_ = den;
        return lhs * rhs;
    }

    friend BigFraction operator/(const BigFraction& lhs, const BigInteger& rhs) { // DIVISION / BIN   frac / int
        if (rhs == 0) {
            throw std::invalid_argument("Error! Deviding by zero is prohibited!");
        }
        return lhs * BigFraction(1, rhs);
    }

    friend BigFraction operator/(const BigInteger& lhs, const BigFraction& rhs) { // DIVISION / BIN   int / frac
        if (rhs.num_ == 0) {
            throw std::invalid_argument("Error! Deviding by zero is prohibited!");
        }
        return lhs * BigFraction(rhs.den_, rhs.num_);
    }

    BigFraction& operator+=(const BigFraction& frac) { // +=  frac += frac
        *this = *this + frac;
        return *this;
    }

    BigFraction& operator+=(const BigInteger& other) { // +=  frac += int
        *this = *this + BigFraction(other, 1);
        return *this;
    }

    BigFraction& operator-=(const BigFraction& frac) { // -=  frac -= frac
        *this = *this - frac;
        return *this;
    }

    BigFraction& operator-=(const BigInteger& other) { // -=  frac -= int
        *this = *this - BigFraction(other, 1);
        return *this;
    }

    BigFraction& operator*=(const BigFraction& frac) {
        *this = *this * frac;
        return *this;
    }

    BigFraction& operator*=(const BigInteger& other) {
        *this = *this * BigFraction(other, 1);
        return *this;
    }

    BigFraction& operator/=(const BigFraction& frac) {
        *this = *this / frac;
        return *this;
    }

    BigFraction& operator/=(const BigInteger& other) {
        *this = *this / BigFraction(other, 1);
        return *this;
    }

    friend bool operator<(BigFraction lhs, BigFraction rhs) {  // <    frac < frac
        BigInteger dena = lhs.den_;
        BigInteger denb = rhs.den_;

        BigInteger temp_gcd = gcd (dena, denb);
        dena /= temp_gcd;
        denb /= temp_gcd;

        lhs.num_ = Karacuba(lhs.num_, denb);
        rhs.num_ = Karacuba(rhs.num_, dena);

        if (lhs.num_ < rhs.num_) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator<(const BigFraction& lhs, const BigInteger& other) {  // <    frac < int
        return lhs < BigFraction(other, 1);
    }

    friend bool operator<(const BigInteger& other, const BigFraction& lhs) {  // <    int < frac
        return BigFraction(other, 1) < lhs;
    }

    friend bool operator>(const BigFraction& lhs, const BigFraction& rhs) { //  >   frac > frac
        return rhs < lhs;
    }

    friend bool operator>(const BigFraction& lhs, const BigInteger& other) { //  >   frac > int
        return BigFraction(other, 1) < lhs;
    }

    friend bool operator>(const BigInteger& other, const BigFraction& lhs) { //  >   int > frac
        return lhs < BigFraction(other, 1);
    }

    friend bool operator<=(const BigFraction& lhs, const BigFraction& rhs) {  // <=    frac <= frac
        return !(lhs > rhs);
    }

    friend bool operator<=(const BigFraction& lhs, const BigInteger& other) { //   <=     frac <= int
        return !(lhs > BigFraction(other, 1));
    }

    friend bool operator<=(const BigInteger& other, const BigFraction& lhs) { // <=    int <= frac
        return !(BigFraction(other, 1) > lhs);
    }

    friend bool operator>=(const BigFraction& lhs, const BigFraction& rhs) {  // >=    frac >= frac
        return !(lhs < rhs);
    }

    friend bool operator>=(const BigFraction& lhs, const BigInteger& other) { //   >=     frac >= int
        return !(lhs < BigFraction(other, 1));
    }

    friend bool operator>=(const BigInteger& other, const BigFraction& lhs) { // >=    int >= frac
        return !(BigFraction(other, 1) < lhs);
    }

    friend bool operator==(BigFraction lhs, BigFraction rhs) {  // ==    frac == frac
        BigInteger dena = lhs.den_;
        BigInteger denb = rhs.den_;

        BigInteger temp_gcd = gcd (dena, denb);
        dena /= temp_gcd;
        denb /= temp_gcd;

        lhs.num_ = Karacuba(lhs.num_, denb);
        rhs.num_ = Karacuba(rhs.num_, dena);

        if (lhs.num_ == rhs.num_) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator==(const BigFraction& lhs,  const BigInteger& other) {  // ==    frac == int
        return (lhs == BigFraction(other, 1));
    }

    friend bool operator==(const BigInteger& other, const BigFraction& lhs) {  // ==    int == frac
        return (lhs == BigFraction(other, 1));
    }

    friend bool operator!=(const BigFraction& lhs, const BigFraction& rhs) { // !=    frac != frac
        return !(lhs == rhs);
    }

    friend bool operator!=(const BigFraction& lhs, const BigInteger& other) { // !=    frac != int
        return !(lhs == BigFraction(other, 1));
    }

    friend bool operator!=(const BigInteger& other, const BigFraction& lhs) { // !=    int != frac
        return !(lhs == BigFraction(other, 1));
    }


    friend std::ostream& operator<<(std::ostream& out, const BigFraction& fract); // COUT
    friend std::istream& operator>>(std::istream& is, BigFraction& fract); // CIN

private:
    BigInteger num_, den_;

    void op() {
        BigInteger temp_gcd = gcd(num_, den_);
        num_ /= temp_gcd;
        den_ /= temp_gcd;
    }

    // void delmin() {
    //     if (den_ < 0) {
    //         den_ *= -1;
    //         num_ *= -1;
    //     }
    // }

    void togood() {
        this -> op ();
        //this -> delmin();
    }
};

std::ostream& operator<<(std::ostream& out, const BigFraction& fract) {
    out << fract.num_ << '/' << fract.den_;
    return out;
}

// std::istream& operator>>(std::istream& is, BigFraction& fract) {
//     is >> fract.num_ >> fract.den_;
//     fract.togood();
//     return is;
// }
