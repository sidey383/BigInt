#include <stdexcept>
#include <string.h>
#include "bigint.h"

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

Decimal::Decimal(Decimal &decimal) {
    this->Negative = decimal.Negative;
    this->Value = decimal.Value;
}

Decimal::Decimal(std::string str) {
    int size = str.size();
    char first = str[size-1];
    if (first == '-') {
        this->Negative = true;
        size--;
    }
    if (first == '+') {
        size++;
    }
    for (int i = 0; i < size; i++) {
        if (this->Value[i] < '0' || this->Value[i] > '9') {
            throw std::invalid_argument("NaN");
        }
    }
    this->Value = str.substr(0, size+1);
}

Decimal::Decimal(char* str) {
    int size = strlen(str);
    char first = str[size-1];
    if (first == '-') {
        this->Negative = true;
        size--;
    } else {
        this->Negative = false;
    }
    if (first == '+') {
        size++;
    }
    for (int i = 0; i < size; i++) {
        if (this->Value[i] < '0' || this->Value[i] > '9') {
            throw std::invalid_argument("NaN");
        }
    }
    this->Value = std::string(str, 0, size-1);
}




