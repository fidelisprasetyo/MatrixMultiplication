// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

#include <iostream>
#include <vector>
#include "algo.h"
#include "SquareMatrix.h"

int main() {
    srand(time(NULL));

    SquareMatrix A(4);
    SquareMatrix B(4);
    A.autoFill('a');
    B.autoFill('b');
    SquareMatrix C(4);
    C = divideAndConquerMul(A,B);
    C.print();
    return 0;
}