#pragma once
#include <string>

class Decimal {

    bool Negative = false;

    std::string Value = "";
private:

    void removeZero();

public:

    Decimal();

    explicit Decimal(int);

    explicit Decimal(long);

    Decimal(const Decimal&);

    explicit Decimal(const std::string);

    explicit Decimal(const char* const);

    std::string getAsString() const;

    Decimal operator+ (const Decimal&) const;

    Decimal operator- (const Decimal&) const;

    Decimal operator- () const;

    Decimal operator/ (const Decimal) const;

    Decimal operator* (const Decimal) const;

    bool operator< (const Decimal&) const;

    bool operator== (const Decimal&) const;

    bool operator> (const Decimal&) const;

    bool operator<= (const Decimal&) const;

    bool operator>= (const Decimal&) const;

    friend std::ostream& operator<< (std::ostream &out, const Decimal &point);

};
