#include <iostream>
#include <vector>
#include <math.h>
#include "SquareMatrix.h"

bool isPowerOfTwo(int n) {
    if (n == 0) {
        return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

void bruteForceMul(const SquareMatrix& M1, const SquareMatrix& M2) {
    if(M1.getSize() != M2.getSize() || !isPowerOfTwo(M1.getSize()) || !isPowerOfTwo(M2.getSize())) {
        std::cout << "Invalid matrix sizes!\n";
        return;
    }
    std::cout << "Multiplication!\n";
    return;
}    

int main() {
    SquareMatrix M1(5);
    SquareMatrix M2(5);
    bruteForceMul(M1, M2);
    return 0;
}