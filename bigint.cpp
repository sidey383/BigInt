#include <stdexcept>
#include <iostream>
#include "bigint.h"

void Decimal::removeZero() {
    int count = 0;
    while (this->Value[count] == '0') {
        count++;
    }
    if (this->Value.size() == count)
        this->Value = "0";
    else
        this->Value = this->Value.substr(count, this->Value.size() - count);
}

Decimal::Decimal() {
    Negative = false;
    this->Value = "0";
}

Decimal::Decimal(int a){
    if(a < 0) {
        Negative = true;
        a = -a;
    }
    do {
        int c = a%10;
        this->Value = (char)(c +'0') + this->Value;
        a=a/10;
    } while(a > 0);
}

Decimal::Decimal(long a){
    if(a < 0) {
        Negative = true;
        a = -a;
    }
    do {
        int c = a%10;
        this->Value = (char)(c +'0') + this->Value;
        a=a/10;
    } while(a > 0);
}

Decimal::Decimal(const Decimal &decimal) {
    this->Negative = decimal.Negative;
    this->Value = decimal.Value;
}

Decimal::Decimal(std::string str) {
    size_t size = str.size();
    char first = str[0];
    int hasFirst = 0;
    if (first == '-') {
        this->Negative = true;
        hasFirst = 1;
    } else {
        this->Negative = false;
    }
    if (first == '+') {
        hasFirst = 1;
    }
    for (int i = hasFirst; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("NaN");
        }
    }
    this->Value = str.substr(hasFirst, size-hasFirst);
    this->removeZero();
}

Decimal::Decimal(const char* const str) {
    size_t size = strlen(str);
    char first = str[0];
    int hasFirst = 0;
    if (first == '-') {
        this->Negative = true;
        hasFirst = 1;
    } else {
        this->Negative = false;
    }
    if (first == '+') {
        hasFirst = 1;
    }
    for (int i = hasFirst; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("NaN");
        }
    }
    this->Value = std::string(str, hasFirst, size-hasFirst);
    this->removeZero();
}

Decimal Decimal::operator+ (const Decimal& val) const {
    if(val.Negative != this->Negative) {
        return val - (-*this);
    }
    if(*this <= val) {
        Decimal dec(val);
        int remains = 0;
        int i = 1;
        while(i <= this->Value.size() || remains > 0) {
            int result = remains;
            if(i <= this->Value.size()) {
                result += this->Value[this->Value.size() - i] - '0';
            }
            if(i <= dec.Value.size()) {
                result += dec.Value[dec.Value.size() - i] - '0';
                dec.Value[dec.Value.size() - i] = (char)('0' + (result%10));
                remains = result/10;
            } else {
                dec.Value = (char)('0' + (result%10)) + dec.Value;
                remains = result/10;
            }
            ++i;
        }
        return dec;
    } else {
        Decimal dec(*this);
        int remains = 0;
        int i = 1;
        while(i <= val.Value.size() || remains > 0) {
            int result = remains;
            if(i <= val.Value.size()) {
                result += val.Value[val.Value.size() - i] - '0';
            }
            if(i <= dec.Value.size()) {
                result += dec.Value[dec.Value.size() - i] - '0';
                dec.Value[dec.Value.size() - i] = (char)('0' + (result%10));
                remains = result/10;
            } else {
                dec.Value = (char)('0' + (result%10)) + dec.Value;
                remains = result/10;
            }
            ++i;
        }
        return dec;
    }
}

Decimal Decimal::operator+= (const Decimal& val) {
    Decimal dec = *this + val;
    this->Value = dec.Value;
    this->Negative = dec.Negative;
    return *this;
}

Decimal Decimal::operator- (const Decimal& val) const {
    if(val.Negative != this->Negative) {
        return *this + (-val);
    }
    if(*this <= val) {
        Decimal dec(val);
        int busy = 0;
        int i = 1;
        while(i <= this->Value.size() || busy > 0) {
            int result = -busy;
            if(i <= this->Value.size()) {
                result -= this->Value[this->Value.size() - i] - '0';
            }
            result += dec.Value[dec.Value.size() - i] - '0';
            if(result < 0) {
                result += 10;
                busy = 1;
            }
            dec.Value[dec.Value.size() - i] = (char)('0' + result);
            ++i;
        }
        dec.removeZero();
        return -dec;
    } else {
        Decimal dec(*this);
        int busy = 0;
        int i = 1;
        while(i <= val.Value.size() || busy > 0) {
            int result = -busy;
            if(i <= val.Value.size()) {
                result -= val.Value[val.Value.size() - i] - '0';
            }
            result += dec.Value[dec.Value.size() - i] - '0';
            if(result < 0) {
                result += 10;
                busy = 1;
            } else {
                busy = 0;
            }
            dec.Value[dec.Value.size() - i] = (char)('0' + result);
            ++i;
        }
        dec.removeZero();
        return dec;
    }
}

Decimal Decimal::operator* (const Decimal& multiplier) const {
    Decimal result;

    for(int i = 0; i < this->Value.size(); i++) {
        for(int j = 0; j < multiplier.Value.size(); j++) {
            Decimal val = Decimal((multiplier.Value[j] - '0') * (this->Value[i] - '0'));
            val.Value = val.Value + std::string(this->Value.size() - i + multiplier.Value.size() - j - 2, '0');
            result = result + val;
        }
    }

    result.Negative = this->Negative ^ multiplier.Negative;
    result.removeZero();
    return result;
}

Decimal average(const Decimal& val1, const Decimal& val2) {
    Decimal result;
    size_t size1 = val1.Value.size();
    size_t size2 = val2.Value.size();
    size_t max = size1 < size2 ? size2 : size1;
    for(size_t i = 1; i <= max; i++) {
        int sum = 0;
        if(i <= size1)
            sum += val1.Value[size1 - i] - '0';
        if(i <= size2)
            sum += val2.Value[size2 - i] - '0';
        result += Decimal((char)(sum/2 + '0') + std::string(i-1, '0'));
        if(sum % 2 != 0 && i > 1) {
            result += Decimal((char)('5') + std::string(i-2, '0'));
        }
    }
    return result;
}

Decimal Decimal::operator/ (const Decimal& divider) const {
    if(divider == Decimal())
        exit((int)0xc0000094);
    if(*this<divider)
        return Decimal();
    if(*this == divider) {
        return Decimal(1);
    }
    bool negative = this->Negative ^ divider.Negative;
    int a = this->Value.size() - divider.Value.size();
    Decimal min = Decimal('1' + std::string(a == 0 ? 0 : a - 1, '0'));
    Decimal max = Decimal('1' + std::string(a == 0 ? 1 : a + 1, '0'));
    while(max - min != Decimal(1)) {
        Decimal averageV = average(max, min);;
        Decimal calcResult = averageV * divider;
        if(calcResult == *this) {
            averageV.Negative = negative;
            return averageV;
        }
        if(calcResult > *this) {
            max = averageV;
        } else {
            min = averageV;
        }
    }
    min.Negative = negative;
    return min;
}

Decimal Decimal::operator-() const {
    Decimal ret(*this);
    ret.Negative = !ret.Negative;
    return ret;
}

std::ostream& operator<< (std::ostream &out, Decimal const& value) {
    if(value.Negative && value.Value != "0")
        out << '-';
    out << value.Value;
    return out;
}

bool Decimal::operator>= (const Decimal& right) const {
    if (right.Value.size() == this->Value.size()) {
        for (int i = 0; i < this->Value.size(); i++)
            if (right.Value[i] != this->Value[i])
                return right.Value[i] < this->Value[i];
        return true;
    } else {
        return right.Value.size() < this->Value.size();
    }
}

bool Decimal::operator<= (const Decimal& right) const {
    if (this->Value.size() == right.Value.size()) {
        for (int i = 0; i < right.Value.size(); i++)
            if (this->Value[i] != right.Value[i])
                return this->Value[i] < right.Value[i];
        return true;
    } else {
        return this->Value.size() < right.Value.size();
    }
}

bool Decimal::operator== (const Decimal& right) const {
    if (this->Value.size() == right.Value.size()) {
        for (int i = 0; i < right.Value.size(); i++)
            if (this->Value[i] != right.Value[i])
                return false;
        return true;
    } else {
        return false;
    }
}

bool Decimal::operator!= (const Decimal& right) const {
    return !(*this == right);
}


bool Decimal::operator> (const Decimal& right) const {
    if (right.Value.size() == this->Value.size()) {
        for (int i = 0; i < this->Value.size(); i++)
            if (right.Value[i] != this->Value[i])
                return right.Value[i] < this->Value[i];
        return false;
    } else {
        return right.Value.size() < this->Value.size();
    }
}

bool Decimal::operator<(const Decimal &right) const {
    if (this->Value.size() == right.Value.size()) {
        for (int i = 0; i < right.Value.size(); i++)
            if (this->Value[i] != right.Value[i])
                return this->Value[i] < right.Value[i];
        return false;
    } else {
        return this->Value.size() < right.Value.size();
    }
}
