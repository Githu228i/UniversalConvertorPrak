#pragma once
#include <exception>
#include <iostream>
#include<algorithm>

int gcd1(int first_number, int second_number) {
    if (second_number == 0) return first_number;
    return gcd1(second_number, first_number % second_number);
}

int gcd(int first_number, int second_number) {
    return abs(gcd1(first_number, second_number));
}

class BigFraction {
public:
    BigFraction() : num_(0), den_(1) {} // DEFAULT

    BigFraction(int num, int den) : num_(num), den_(den) { // CONSTRUCTOR INT INT
        if (den == 0) {
            throw "ULYALA";
        }
        this -> togood();
    }

    explicit BigFraction(int num) : num_(num), den_(1) {} // CONSTRUCTOR INT

    BigFraction(const BigFraction& other) { // CONSTRUCTOR COPY
        num_ = other.num_;
        den_ = other.den_;
    }

    ~BigFraction() = default; // DESTRUCTOR DEFAULT

    int num() const { return num_; } // SETTER NUM
    int den() const { return den_; } // SETTER DEN

    BigFraction& operator=(const BigFraction& other) { // EQUAL =
        num_ = other.num_;
        den_ = other.den_;
        return *this;
    }

    BigFraction& operator=(int nn) { // EQUAL = int
        num_ = nn;
        den_ = 1;
        return *this;
    }

    BigFraction operator-() { // MINUS - UNO
        BigFraction res = *this;
        res.num_ = -1 * num_;
        res.den_ = den_;
        return res;
    }

    BigFraction operator+() { // PLUS + UNO
        return *this;
    }

    friend BigFraction operator++(BigFraction& frac) { // PLUS PREF ++ UNO
        frac.num_ += frac.den_;
        return frac;
    }

    friend BigFraction operator++(BigFraction& frac, int notused) {// PLUS POST ++ UNO
        BigFraction res = frac;
        frac.num_ += frac.den_;
        return res;
    }

    friend BigFraction operator--(BigFraction& frac) { // MINUS PREF -- UNO
        frac.num_ -= frac.den_;
        return frac;
    }

    friend BigFraction operator--(BigFraction& frac, int notused) {// MINUS POST -- UNO
        BigFraction res = frac;
        frac.num_ -= frac.den_;
        return res;
    }

    friend BigFraction operator+(BigFraction lhs, BigFraction rhs) { // PLUS + BIN
        int dena = lhs.den_;
        int denb = rhs.den_;

        lhs.num_ *= denb;
        lhs.den_ *= denb;
        rhs.num_ *= dena;
        rhs.den_ *= dena;

        lhs.num_ += rhs.num_;
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator+(const BigFraction& lhs, int nn) { // PLUS + BIN frac + int
        return lhs + BigFraction(nn, 1);
    }

    friend BigFraction operator+(int nn, const BigFraction& lhs) { // PLUS + BIN int + frac
        return lhs + BigFraction(nn, 1);
    }

    friend BigFraction operator-(const BigFraction& lhs, BigFraction rhs) { // MINUS - BIN frac - frac
        return lhs + (-rhs);
    }

    friend BigFraction operator-(const BigFraction& lhs, int nn) { // MINUS - BIN frac - int
        return lhs + (-nn);
    }

    friend BigFraction operator-(int nn, BigFraction lhs) { // MINUS - BIN int - frac
        return -lhs + nn;
    }

    friend BigFraction operator*(BigFraction lhs, const BigFraction& rhs) { // MULTIPLICATION *
        lhs.num_ *= rhs.num_;
        lhs.den_ *= rhs.den_;
        return lhs;
    }

    friend BigFraction operator*(BigFraction lhs, int nn) { // MULTIPLICATION * BIN     frac * int
        lhs.num_ *= nn;
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator*(int nn, BigFraction lhs) { // MULTIPLICATION * BIN    int * frac
        lhs.num_ *= nn;
        lhs.togood();
        return lhs;
    }

    friend BigFraction operator/(const BigFraction& lhs, BigFraction rhs) { // DIVISION / BIN   frac / frac
        int den = rhs.den_;
        rhs.den_ = rhs.num_;
        rhs.num_ = den;
        return lhs * rhs;
    }

    friend BigFraction operator/(const BigFraction& lhs, int nn) { // DIVISION / BIN   frac / int
        if (nn == 0) {
            throw "ULYAYAYAYYA";
        }
        return lhs * BigFraction(1, nn);
    }

    friend BigFraction operator/(int nn, const BigFraction& lhs) { // DIVISION / BIN   int / frac
        return nn * BigFraction(lhs.den_, lhs.num_);
    }

    BigFraction operator+=(const BigFraction& frac) { // +=  frac += frac
        *this = *this + frac;
        return *this;
    }

    BigFraction operator+=(int nn) { // +=  frac += int
        *this = *this + nn;
        return *this;
    }

    BigFraction operator-=(const BigFraction& frac) { // -=  frac -= frac
        *this = *this - frac;
        return *this;
    }

    BigFraction operator-=(int nn) { // -=  frac -= int
        *this = *this - nn;
        return *this;
    }

    BigFraction operator*=(const BigFraction& frac) {
        *this = *this * frac;
        return *this;
    }

    BigFraction operator*=(int nn) {
        *this = *this * nn;
        return *this;
    }

    BigFraction operator/=(const BigFraction& frac) {
        *this = *this / frac;
        return *this;
    }

    BigFraction operator/=(int nn) {
        *this = *this / nn;
        return *this;
    }

    friend bool operator<(BigFraction lhs, BigFraction rhs) {  // <    frac < frac
        int dena = lhs.den_;
        int denb = rhs.den_;

        lhs.num_ *= denb;
        lhs.den_ *= denb;
        rhs.num_ *= dena;
        rhs.den_ *= dena;

        if (lhs.num_ < rhs.num_) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator<(const BigFraction& lhs, int nn) {  // <    frac < int
        return lhs < BigFraction(nn, 1);
    }

    friend bool operator<(int nn, const BigFraction& lhs) {  // <    int < frac
        return BigFraction(nn, 1) < lhs;
    }

    friend bool operator>(const BigFraction& lhs, const BigFraction& rhs) { //  >   frac > frac
        return rhs < lhs;
    }

    friend bool operator>(const BigFraction& lhs, int nn) { //  >   frac > int
        return BigFraction(nn, 1) < lhs;
    }

    friend bool operator>(int nn, const BigFraction& lhs) { //  >   int > frac
        return lhs < BigFraction(nn, 1);
    }

    friend bool operator<=(const BigFraction& lhs, const BigFraction& rhs) {  // <=    frac <= frac
        return !(lhs > rhs);
    }

    friend bool operator<=(const BigFraction& lhs, int nn) { //   <=     frac <= int
        return !(lhs > nn);
    }

    friend bool operator<=(int nn, const BigFraction& lhs) { // <=    int <= frac
        return !(nn > lhs);
    }

    friend bool operator>=(const BigFraction& lhs, const BigFraction& rhs) {  // >=    frac >= frac
        return !(lhs < rhs);
    }

    friend bool operator>=(const BigFraction& lhs, int nn) { //   >=     frac >= int
        return !(lhs < nn);
    }

    friend bool operator>=(int nn, const BigFraction& lhs) { // >=    int >= frac
        return !(nn < lhs);
    }

    friend bool operator==(BigFraction lhs, BigFraction rhs) {  // ==    frac == frac
        int dena = lhs.den_;
        int denb = rhs.den_;

        lhs.num_ *= denb;
        lhs.den_ *= denb;
        rhs.num_ *= dena;
        rhs.den_ *= dena;

        if (lhs.num_ == rhs.num_) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator==(const BigFraction& lhs, int nn) {  // ==    frac == int
        return (lhs == BigFraction(nn, 1));
    }

    friend bool operator==(int nn, const BigFraction& lhs) {  // ==    int == frac
        return (lhs == BigFraction(nn, 1));
    }

    friend bool operator!=(const BigFraction& lhs, const BigFraction& rhs) { // !=    frac != frac
        return !(lhs == rhs);
    }

    friend bool operator!=(const BigFraction& lhs, int nn) { // !=    frac != int
        return !(lhs == nn);
    }

    friend bool operator!=(int nn, const BigFraction& lhs) { // !=    int != frac
        return !(lhs == nn);
    }


    friend std::ostream& operator<<(std::ostream& out, const BigFraction& fract); // COUT
    friend std::istream& operator>>(std::istream& is, BigFraction& fract); // CIN

private:
    int num_, den_;

    void op(int num, int den) {
        num_ /= gcd(num, den);
        den_ /= gcd(num, den);
    }

    void delmin() {
        if (den_ < 0) {
            den_ *= -1;
            num_ *= -1;
        }
    }

    void togood() {
        this -> op (num_, den_);
        this -> delmin();
    }
};

std::ostream& operator<<(std::ostream& out, const BigFraction& fract) {
    out << fract.num_ << '/' << fract.den_;
    return out;
}

std::istream& operator>>(std::istream& is, BigFraction& fract) {
    is >> fract.num_ >> fract.den_;
    fract.togood();
    return is;
}
