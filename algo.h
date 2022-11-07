// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

#pragma once

#include <math.h>   // ceil & floor
#include <iomanip>
#include "SquareMatrix.h"

bool isPowerOfTwo(int n) {
    if (n == 0) {
        return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

bool isMatrixValid(const SquareMatrix& A, const SquareMatrix& B) {
    if(A.size() != B.size() || !isPowerOfTwo(A.size()) || !isPowerOfTwo(B.size())) {
        return false;
    }
    return true;
}

// brute force matrix multiplication
SquareMatrix classicMultiplication(const SquareMatrix& A, const SquareMatrix& B) {
    int n = A.size();
    SquareMatrix C(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                C(i,j) += A(i,k) * B(k,j);
            }
        }
    }
    return C;
}    

SquareMatrix divideAndConquerMul(const SquareMatrix& A, const SquareMatrix& B) {

    SquareMatrix C(A.size());

    // base case: when the quadrant only contains 1 element
    if(A.size() == 1) {
        C(0,0) = A(0,0) * B(0,0);
    }
    // recursive case: divide into quadrants
    else {
        int n = A.size() / 2;

        // initiate the quadrants
        SquareMatrix A_00(n); SquareMatrix B_00(n);
        SquareMatrix A_01(n); SquareMatrix B_01(n);
        SquareMatrix A_10(n); SquareMatrix B_10(n);
        SquareMatrix A_11(n); SquareMatrix B_11(n);

        SquareMatrix C_00(n);
        SquareMatrix C_01(n);
        SquareMatrix C_10(n);
        SquareMatrix C_11(n);

        // fill the quadrants
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                A_00(i,j) = A(i,j);
                A_01(i,j) = A(i,j + n);
                A_10(i,j) = A(i + n,j);
                A_11(i,j) = A(i + n,j + n);

                B_00(i,j) = B(i,j);
                B_01(i,j) = B(i,j + n);
                B_10(i,j) = B(i + n,j);
                B_11(i,j) = B(i + n,j + n);
            }
        }

        // multiply the quadrants
        C_00 = divideAndConquerMul(A_00, B_00) + divideAndConquerMul(A_01, B_10);    // C_00 = (A_00 * B_00) + (A_01 * B_10)
        C_01 = divideAndConquerMul(A_00, B_01) + divideAndConquerMul(A_01, B_11);    // C_01 = (A_00 * B_01) + (A_01 * B_11)
        C_10 = divideAndConquerMul(A_10, B_00) + divideAndConquerMul(A_11, B_10);    // C_10 = (A_10 * B_00) + (A_11 * B_10)
        C_11 = divideAndConquerMul(A_10, B_01) + divideAndConquerMul(A_11, B_11);    // C_11 = (A_10 * B_01) + (A_11 * B_11)

        // combine into 1 matrix
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                C(i,j) = C_00(i,j);
                C(i,j + n) = C_01(i,j);
                C(i + n,j) = C_10(i,j);
                C(i + n,j + n) = C_11(i,j);
            }
        }
    }
    return C;
}
SquareMatrix strassenAlgorithm(const SquareMatrix& A, const SquareMatrix& B) {

    SquareMatrix C(A.size());

    // base case: when the quadrant only contains 1 element
    if(A.size() == 1) {
        C(0,0) = A(0,0) * B(0,0);
    }
    // recursive case: divide into quadrants
    else {
        int n = A.size() / 2;

        // initiate the quadrants
        SquareMatrix A_00(n); SquareMatrix B_00(n); SquareMatrix C_00(n);
        SquareMatrix A_01(n); SquareMatrix B_01(n); SquareMatrix C_01(n);
        SquareMatrix A_10(n); SquareMatrix B_10(n); SquareMatrix C_10(n);
        SquareMatrix A_11(n); SquareMatrix B_11(n); SquareMatrix C_11(n);

        SquareMatrix P0(n);
        SquareMatrix P1(n);
        SquareMatrix P2(n);
        SquareMatrix P3(n);
        SquareMatrix P4(n);
        SquareMatrix P5(n);
        SquareMatrix P6(n);

        // fill the quadrants
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                A_00(i,j) = A(i,j);
                A_01(i,j) = A(i,j + n);
                A_10(i,j) = A(i + n,j);
                A_11(i,j) = A(i + n,j + n);

                B_00(i,j) = B(i,j);
                B_01(i,j) = B(i,j + n);
                B_10(i,j) = B(i + n,j);
                B_11(i,j) = B(i + n,j + n);
            }
        }

        // multiply the quadrants
        P0 = strassenAlgorithm(A_00, B_01 - B_11);
        P1 = strassenAlgorithm(A_00 + A_01, B_11);
        P2 = strassenAlgorithm(A_10 + A_11, B_00);
        P3 = strassenAlgorithm(A_11, B_10 - B_00);
        P4 = strassenAlgorithm(A_00 + A_11, B_00 + B_11);
        P5 = strassenAlgorithm(A_01 - A_11, B_10 + B_11);
        P6 = strassenAlgorithm(A_00 - A_10, B_00 + B_01);

        C_00 = P3 + P4 + P5 - P1;
        C_01 = P0 + P1;
        C_10 = P2 + P3;
        C_11 = P0 - P2 + P4 - P6;

        // combine into 1 matrix
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                C(i,j) = C_00(i,j);
                C(i,j + n) = C_01(i,j);
                C(i + n,j) = C_10(i,j);
                C(i + n,j + n) = C_11(i,j);
            }
        }
    }
    return C;
}