#pragma once
#include <string>

class Decimal {

    bool Negative = false;

    std::string Value = "";

public:

    Decimal();

    Decimal(int);

    Decimal(long);

    Decimal(Decimal&);

    Decimal(std::string);

    Decimal(char*);

    Decimal& operator+ (Decimal&);

    Decimal& operator- (Decimal);

    void operator- ();

    Decimal& operator/ (Decimal);

    Decimal& operator* (Decimal);

    bool operator< (Decimal&);

    bool operator== (Decimal);

    bool operator> (Decimal&);

    bool operator<= (Decimal&);

    bool operator>= (Decimal&);

};
