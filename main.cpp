// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

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

bool isMatrixValid(const SquareMatrix& M1, const SquareMatrix& M2) {
    if(M1.getSize() != M2.getSize() || !isPowerOfTwo(M1.getSize()) || !isPowerOfTwo(M2.getSize())) {
        return false;
    }
    return true;
}

void bruteForceMul(SquareMatrix& M1, SquareMatrix& M2) {
    int n = M1.getSize();
    SquareMatrix P(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            P[i][j] = 0;
            for(int k = 0; k < n; k++) {
                P[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    P.print();
    return;
}    

int main() {
    srand(time(NULL));
    SquareMatrix M1(4);
    SquareMatrix M2(4);
    M1.randomValues();
    M2.randomValues();
    M1.print();
    M2.print();
    return 0;
}