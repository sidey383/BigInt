#include <iostream>
#include "BigInt.h"

int main() {
    Decimal a("-23");
    Decimal b("-23");
    std::cout << a - b;
    return 0;
}
