#include "bigfraction.h"


std::ostream& operator<<(std::ostream& out, const BigFraction& fract) {
    out << fract.num_ << '/' << fract.den_;
    return out;
}

QDebug operator<<(QDebug out, const BigFraction& val) {
    out.nospace().noquote();
    out << QString::fromStdString(val.num().ToString()) << " / " << QString::fromStdString(val.den().ToString());
    return out;
}

