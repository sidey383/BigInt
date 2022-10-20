#include <stdexcept>
#include <iostream>
#include <string.h>
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
    Negative = a < 0;
    do {
        int c = a%10;
        this->Value = (char)(c +'0') + this->Value;
        a=a/10;
    } while(a > 0);
}

Decimal::Decimal(long a){
    Negative = a < 0;
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
    int size = str.size();
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
    int size = strlen(str);
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
                dec.Value[dec.Value.size() - i] = '0' + (result%10);
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
                dec.Value[dec.Value.size() - i] = '0' + (result%10);
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

Decimal Decimal::operator-() const {
    Decimal ret(*this);
    ret.Negative = !ret.Negative;
    return ret;
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

std::string Decimal::getAsString() const {
    return this->Value;
}

std::ostream& operator<< (std::ostream &out, Decimal const& value) {
    if(value.Negative && value.Value != "0")
        out << '-';
    out << value.Value;
    return out;
}
