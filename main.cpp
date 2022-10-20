#include <iostream>
#include "BigInt.h"

int main() {
    for(int i = -1000; i < 1000; i++) {
        for(int j = -1000; j < 1000; j++) {
            if(j == 0)
                continue;
            if((Decimal(i) / Decimal(j)) != Decimal(i / j)) {
                std::cout<<"error:\n\t"<<Decimal(i)<<"/"<<Decimal(j)<<"="<<(Decimal(i) / Decimal(j))<<"\n";
            }
        }
    }
}
